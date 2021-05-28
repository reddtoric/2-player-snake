# 2-player-snake

Two-player snake game in C++ using Arduino Mega, 32x32 LED matrix, custom shield, and two custom 4-button controllers for Adv. Additive Manufacturing (UIC ENGR 294)

</br>
<p float="left">
<img src="https://media.giphy.com/media/iEMkRfB8JyjEhcMhLR/giphy-downsized.gif" alt="GIF of 2p snake part1"/>
<img src="https://media.giphy.com/media/J6tbl7obMBHApaVlm7/giphy-downsized.gif" alt="GIF of 2p snake part2"/>
</p>

[Original GIF #1](https://media.giphy.com/media/iEMkRfB8JyjEhcMhLR/giphy.gif) | 
[Original GIF #2](https://media.giphy.com/media/J6tbl7obMBHApaVlm7/giphy.gif)

<img src="Images/overview.jpg" width="400"/>

</br></br>

<!-- TOC -->

- [2-player-snake](#2-player-snake)
  - [D-pad Controller PCB](#d-pad-controller-pcb)
  - [Arduino Mega Shield](#arduino-mega-shield)
  - [Case](#case)
  - [Updated Case](#updated-case)

<!-- /TOC -->

(Few more pictures included in _Images/_)

## D-pad Controller PCB

Manually figuring out the routes for all 4 buttons.

<img src="Images/controller-pcb-draft.jpg" width="400"/> <img src="Images/controller-pcb-schematic-routes.jpg" width="400"/>
<img src="Images/controller-pcb.jpg" width="400"/>

Yes, I know the soldering is bad.

## Arduino Mega Shield

Also, manually routed the shield. Here is the mapping of the 16 pin connector socket for LED matrix and the routes to the Arduino Mega pinouts. The correct mapping might be the horizontal mirrored version; I didn't have a connector cable.

<img src="Images/led-routing-guide.jpg" width="400"/>

I only had access to single sided PCB so red PCB routes are on the top/main side and blue routes are on the back that had to be manually connected with wires.

<img src="Images/pcb-schematic-routes.jpg" width="400"/> </br>
<img src="Images/shield-front.jpg" width="400"/>
<img src="Images/shield-back.jpg" width="400"/>

## Case

Planning and designing the controller cases.

<img src="Images/controller-cross-section.jpg" width="400"/>

(Partially) Initial design. I forgot the divot where the soldering on the PCB takes up space. In the original case, you'll see I melted it. Screw holes are not in the CAD because I didn't have enough time to make sure they're were they should be and decided to just drill them.

<img src="Images/case.jpg" width="400"/> <img src="Images/back-cover.jpg" width="400"/> <img src="Images/dpad.jpg" width="400"/>

Putting it all together.

<img src="Images/old-deconstruct.jpg" width="400"/> <img src="Images/old-opened.jpg" width="400"/>

## Updated Case

Added minor changes to the case design. Filet edges, screw holes, tighter tolerances, hole for ethernet cable, and printed with higher quality settings.

<img src="Images/comparison.jpg" width="400"/>

Old:

<img src="Images/old1.jpg" width="400"/>

New:

<img src="Images/new1.jpg" width="300"/> <img src="Images/new2.jpg" width="300"/></br>
<img src="Images/new3.jpg" width="300"/> <img src="Images/new4.jpg" width="300"/>
