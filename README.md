# GVAR Tools

GVAR tools - a set of (crappy) tools for dealing with GVAR data from GOES-13, currently only an image decoder.

## Installation

If you are on Debian/Ubuntu you may want to replace `cmake -DCMAKE_BUILD_TYPE=Release ..` with `cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr ..`

```
git clone https://github.com/Xerbo/GVAR-Tools && cd GVAR-Tools
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j 4
sudo make install
```

## Usage

Included in this repo is a GNURadio script suitable for demodulation.

Once you have your bin file you can decode as easily as:

```
GVAR-Decoder path/to/file.bin
```

Which will dump save channel from the satellite in the format `G13-n.png`

For full use instructions use:

```
GVAR-Decoder --help
```

## TODO

 - Replace simple deframer with something less basic
 - Drop CImg
 - Use something better than nearest neighbor for resizing the images
 - Average between missed rows instead of just copying
 - Use actual values for channel alignment instead of "that looks fine"

## Theory and resources

In this git repo you will find a pdr called `G023_504.02_DCN3_Sect_3.pdf`, this contains the protocol specification.

TL;DR

 - Data is pseudo randomized
 - Data is framed
 - Data is encoded with NRZ-S differential encoding
 - Broadcast in BPSK at 2.11136MSPS

Channel information:

 - Channels 1 and 3 are interleaved, aka 2 rows per frame.
 - Channels 2 and 4 are just transmitted with each other row missing.
 - Channel 5 utilizes blocks 3 through 10 and is 1 line per frame
 - All channels are in a 1.75:1 ratio.
 - All channels are 10 bit

## Credits

I would like to say many thanks to [Aang23](https://github.com/Aang23) for helping me with the pseudo random decoding and *a bit* (pun very much intended) of bit shift work!

## License

See `LICENSE`
