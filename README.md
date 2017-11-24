# Blipper
A camera accessory that inserts computer-recognizable markers into video recordings for automated video editing.

[![Watch the video](https://github.com/evankale/Blipper/blob/master/video.jpg?raw=true)](http://youtu.be/p53PxLBQFAk)

Watch the video: http://youtu.be/p53PxLBQFAk

Scripts
=======
MAGIX/Sony Vegas scripts for automation are available in my VegasScripts repo:
https://github.com/evankale/VegasScripts

If you think these scripts should be ported over to another software, like Adobe, then tell me!

I will do so if there's a demand for it.

The following scripts make use of Blipper markers:

- MarkBlipsInSelectedVideoEvent
  - Finds all blips of a selected video event(inserted by the Blipper) and adds a bookmark at that location.

- SplitBlips
  - Creates splits where blips are made in the left channel audio during the span of the selected video track.

- MapBlipsToMIDI
  - Maps all blips (created by the Blipper) to MIDI notes of an input MIDI file.
  - Requires NAudio.dll (https://github.com/naudio/NAudio)
 
Making a Blipper
================
Source code and schematics are available in the "src" directory to build a single-button Blipper.

But why build an inferior Blipper when you can buy the superior 3-button Blipper straight out of Evan Kale's lab?!

Blippers available for purchase at: https://www.etsy.com/shop/EvanKale

![alt text](https://github.com/evankale/Blipper/blob/master/src/schematics.jpg?raw=true)