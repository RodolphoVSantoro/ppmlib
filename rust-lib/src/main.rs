use rust_lib::load_image;

fn main() {
    let path = std::ffi::CString::new("./target/release/red.png").unwrap();
    let path = path.as_ptr() as *const u8;
    let image = load_image(path);
    

    // println!("Hello, world!{:?}", unsafe {(**image).red});
}
