#!/bin/bash

meshmagick transform -scale=4/4/4 Track.mesh
meshmagick transform -xalign=center -yalign=center -zalign=center Track.mesh
meshmagick transform -translate=0/0/-130 Track.mesh
