extern crate dirs;

extern crate rodio;

extern crate web_view;

use web_view::*;

use std::{fs::File,io::BufReader};

use rodio::Source;

const ALLOWED_TYPES: &'static [&'static str] = &["mp3", "wav", "ogg", "flac"];

fn main() {
    /*
    let device = rodio::default_output_device().unwrap();

    let mut url: String = "".to_string();

    let path_buf = dirs::audio_dir().unwrap();
    let mut folders = Vec::new();
    folders.push(path_buf);
    let mut folder_index: usize = 0;
    while folder_index < folders.len() {
        for entry in folders[folder_index].read_dir().expect("read_dir call failed") {
            if let Ok(entry) = entry {
                if entry.path().is_dir() {
                    folders.push(entry.path());
                }

                else if entry.path().is_file() {
                    if ALLOWED_TYPES.contains(&&entry.path().extension().unwrap().to_string_lossy().to_mut()[..]) {
                        println!("{:?}", entry.path());
                        url = entry.path().to_str().unwrap().to_string();
                    }
                }
            }
        }

        folder_index += 1;
    }

    let file = File::open(url).unwrap();
    let source = rodio::Decoder::new(BufReader::new(file)).unwrap();
    rodio::play_raw(&device, source.convert_samples());*/

    let mut webview = web_view::builder()
        .title("Minimal webview example")
        .content(Content::Url("https://en.m.wikipedia.org/wiki/Main_Page"))
        .size(800, 600)
        .resizable(true)
        .debug(true)
        .user_data(())
        .invoke_handler(|_webview, _arg| Ok(()))
        .build().unwrap();

    webview.set_color((156, 39, 176));

    let res =  match webview.run() {
        Ok(v) => v,
        Err(e) => println!("error: {:?}", e),
    };
}