fn main() {
    cxx_build::bridge("src/lib.rs")
        .static_flag(true)
        .std("c++17")
        .compile("synth");

    println!("cargo:rerun-if-changed=src/synth.rs");
}