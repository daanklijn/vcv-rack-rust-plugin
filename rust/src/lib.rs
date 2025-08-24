use ffi::*;
//#[cxx::bridge(namespace = "org::environment")]

mod wavetable;

use cxx::CxxVector;
use wavetable::SINE_TABLE;

#[cxx::bridge]
mod ffi {

    extern "Rust" {
        type Synth;
        fn new_synth() -> Box<Synth>;
        fn next_sample(&mut self)->f32;
        fn set_frequency(&mut self, frequency: f32);
    }
}

fn new_synth () -> Box<Synth> {
    Box::new(Synth{ frequency: 2.0, wavetable_index: 0.0})
}

struct Synth {
    wavetable_index: f32,
    frequency: f32,
}

impl Synth {
    fn next_sample(&mut self) -> f32{
        self.wavetable_index += self.frequency * 1024.0 / 44100.0;
        if(self.wavetable_index >= 1024.0) {
            self.wavetable_index -= 1024.0;
        }
        return SINE_TABLE[self.wavetable_index as usize] as f32;
    }

    fn set_frequency(&mut self, frequency: f32) {
        self.frequency = frequency;
    }
}