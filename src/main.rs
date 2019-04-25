#![windows_subsystem = "windows"]

extern crate web_view;

use web_view::*;

fn main() {
    println!("Hello, world!");
    web_view::builder()
        .title("Sgnow")
        .content(Content::Url("https://gnowbros.com"))
        .size(1280, 720)
        .resizable(true)
        .debug(true)
        .user_data(())
        .invoke_handler(|_webview, _arg| Ok(()))
        .run()
        .unwrap();
}
