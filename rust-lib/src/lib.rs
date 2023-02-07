use image::GenericImageView;

#[repr(C)]
pub struct RGB {
    pub red: u8,
    pub green: u8,
    pub blue: u8,
}

#[repr(C)]
pub struct Image {
    pub pixels: *mut *mut RGB,
    pub width: u32,
    pub height: u32,
}

#[no_mangle]
pub fn load_image(path: *const u8) -> Image {
    let path = unsafe { std::ffi::CStr::from_ptr(path as *const i8) };
    let path = path.to_str().unwrap();

    let image = image::open(path).unwrap();

    let dimensions = image.dimensions();

    let mut pixels = Vec::new();

    for y in 0..dimensions.1 {
        let mut row = Vec::new();
        for x in 0..dimensions.0 {
            let pixel = image.get_pixel(x, y);
            let rgb = RGB {
                red: pixel[0],
                green: pixel[1],
                blue: pixel[2],
            };
            row.push(rgb);
        }
        pixels.push(row);
    }

    let mut pixels = pixels
        .into_iter()
        .map(|row| {
            let mut row = row.into_boxed_slice();
            let ptr = row.as_mut_ptr();
            std::mem::forget(row);
            ptr
        })
        .collect::<Vec<_>>();

    let ptr = pixels.as_mut_ptr();
    std::mem::forget(pixels);

    Image {
        pixels: ptr,
        width: dimensions.0,
        height: dimensions.1,
    }
}

#[no_mangle]
pub fn add_numbers(a: i32, b: i32) -> i32 {
    a + b
}

// #[no_mangle]
// pub extern "C" fn add(name: *mut *mut u8, age: u8) -> Person {
//     unsafe {
//         println!("Hello, world! {:#?} {}", **name, age);
//     }
//     Person { name, age }
// }

// #[cfg(test)]
// mod tests {
//     use super::*;

//     #[test]
//     fn it_works() {
//         let result = add(2, 2);
//         assert_eq!(result, 4);
//     }
// }
