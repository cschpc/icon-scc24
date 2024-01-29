#! /usr/bin/env python

# ICON
#
# ------------------------------------------
# Copyright (C) 2004-2024, DWD, MPI-M, DKRZ, KIT, ETH, MeteoSwiss
# Contact information: icon-model.org
# See AUTHORS.TXT for a list of authors
# See LICENSES/ for license information
# SPDX-License-Identifier: BSD-3-Clause
# ------------------------------------------

# -*- coding: utf-8 -*-
#==============================================================================
#==============================================================================

import sys
import os


#the 40 levels, 6020 meters depth
#level_dz = [  12.0,   10.0,   10.0,   10.0,   10.0,   10.0,   13.0,   15.0,   20.0,   25.0,
              #30.0,   35.0,   40.0,   45.0,   50.0,   55.0,   60.0,   70.0,   80.0,   90.0,
             #100.0,  110.0,  120.0,  130.0,  140.0,  150.0,  170.0,  180.0,  190.0,  200.0,
             #220.0,  250.0,  270.0,  300.0,  350.0,  400.0,  450.0,  500.0,  500.0,  600.0 ]

## the 56 levels, 6132 meters depth
#level_dz  =  [ 12.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   11.0,   11.0,   12.0,
               #13.0,   14.0,   15.0,   16.0,   17.0,   18.0,   20.0,   22.0,   24.0,   26.0,
               #29.0,   33.0,   36.0,   39.0,   42.0,   45.0,   48.0,   52.0,   56.0,   60.0,
               #64.0,   68.0,   72.0,   76.0,   80.0,   85.0,   90.0,   95.0,  100.0,  106.0,
              #115.0,  130.0,  145.0,  160.0,  175.0,  190.0,  210.0,  230.0,  260.0,  290.0,
              #330.0,  370.0,  410.0,  460.0,  510.0, 580.0 ]

##64 levels, 6017 meters depth
#level_dz = [ 12.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   11.0,   11.0,   12.0,
             #13.0,   14.0,   15.0,   16.0,   17.0,   18.0,   19.0,   20.0,   22.0,   24.0,
             #26.0,   28.0,   30.0,   33.0,   36.0,   39.0,   42.0,   45.0,   48.0,   52.0,
             #56.0,   60.0,   64.0,   68.0,   73.0,   78.0,   83.0,   88.0,   94.0,  100.0,
             #106.0,  112.0,  118.0,  125.0,  132.0, 139.0,  147.0,  155.0,  163.0,  172.0,
             #181.0,  190.0,  200.0,  210.0,  220.0, 230.0,  240.0,  250.0,  250.0,  250.0,
             #250.0,  250.0,  250.0,  250.0 ]

##128 levels, 6362 meters depth
#level_dz = [ 11.0,    9.0,     8.0,   8.0,     8.0,    8.0,    8.0,    8.0,    8.0,    8.0,
              #8.0,    8.0,    8.0,    8.25,   8.5,    8.75,   9.0,   9.25,    9.5,   9.75,
             #10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,
             #10.5,   11.0,   11.5,   12.0,   12.5,   13.0,   13.5,   14.0,   14.5,   15.0,
             #15.5,   16.0,   16.5,   17.0,   17.5,   18.0,   18.5,   19.0,   19.5,   20.0, 
             #20.5,   21.0,   21.5,   22.0,   22.5,   23.0,   23.5,   24.0,   24.5,   25.0,
             #25.5,   26.0,   26.5,   27.0,   28.5,   29.0,   29.5,   30.0,   30.5,   31.0,
             #31.0,   32.0,   33.0,   34.0,   35.0,   36.0,   37.0,   38.0,   39.0,   40.0,
             #42.0,   44.0,   46.0,   48.0,   50.0,   52.0,   54.0,   56.0,   58.0,   60.0,
             #62.0,   64.0,   66.0,   68.0,   70.0,   72.0,   74.0,   76.0,   78.0,   80.0,
             #82.0,   84.0,   86.0,   88.0,   90.0,   92.0,   94.0,   96.0,   98.0,  100.0,
            #102.0,  104.0,  106.0,  108.0,  110.0,  112.0,  114.0,  116.0,  118.0,  200.0,
            #200.0,  200.0,  200.0,  200.0,  200.0,  200.0,  200.0,  200.0 ]
             
             
level_dz = [ 12.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,   10.0,
             13.0,   14.0,   15.0,   16.0,   17.0,   18.0,   19.0,   20.0,   22.0,   24.0,
             26.0,   28.0,   30.0,   33.0,   36.0,   39.0,   42.0,   45.0,   48.0,   52.0,
             56.0,   60.0,   64.0,   68.0,   73.0,   78.0,   83.0,   88.0,   94.0,  100.0,
             106.0,  112.0,  118.0,  125.0,  132.0, 139.0,  147.0,  155.0,  163.0,  172.0,
             181.0,  190.0,  200.0,  210.0,  220.0, 230.0,  240.0,  250.0,  250.0,  250.0,
             250.0,  250.0,  250.0,  250.0 ]


noOfLevels=127
depth=0.0
start_calc=1
my_level = [ 8.0 ]*noOfLevels
level_dz=my_level
k=0

min_dz = 0

for k in range(start_calc):
  depth += my_level[k]
  #print(k, ":", my_level[k], depth)

for k in range(start_calc,noOfLevels):
  
  if  depth < 80.0:
    my_level[k] = 3.0
  elif depth < 500:
    #my_level[k] = my_level[k-1] * 1.025
    my_level[k] = max(round(depth * 0.02575), min_dz)
  else:
    my_level[k] = max(round(my_level[k-1] * 1.04 + depth * 0.005), min_dz)
                      
  depth += my_level[k]
  min_dz = my_level[k]
  #print(k, ":", my_level[k], depth, " ratio:",  my_level[k]/my_level[k-1])
 
  #level_dz[k] = round(my_level[k])

#sys.exit()

#  smooth if necessary:
#for i in  range(18):
  #for k in range(start_calc+1,64-1):  
    #if round(my_level[k+1])-round(my_level[k]) < round(my_level[k])-round(my_level[k-1]): 
      ## or my_level[k] < (my_level[k+1]+my_level[k-1])*0.5:
      #my_level[k] = my_level[k-1]*0.6+my_level[k+1]*0.4
 
for k in range(noOfLevels):  
  level_dz[k] = round(my_level[k])

middle_depth = 0.0
middle_depth_array = []
dz_up=0.0
depth=0.0
level=1

for dz in level_dz:
  
  depth += dz
  #ratio = (dz - dz_up) / dz
  if dz_up > 0:
    ratio = dz / dz_up
  else:
    ratio = 0
  middle_depth += (dz + dz_up) * 0.5
  depth_ratio = dz / depth
  print("%3d :  dz=%6.1f, depth=%7.1f,  dz difference=%5.1f,  dz ratio=%5.2f" % (level, dz, depth, dz-dz_up, round(ratio,2)))
  #print(level, ": ", " dz=", dz, " depth=", depth, " dz difference",  dz-dz_up, " dz ratio=", round(ratio,2))
  middle_depth_array.append(middle_depth)
  level+=1
  
  dz_up = dz

print(level_dz)
print(middle_depth_array)


# the new 64 levels
#[12, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 22, 24, 26, 28, 30, 32, 35, 38, 41, 45, 49, 53, 58, 62, 66, 71, 75, 81, 87, 91, 97, 104, 111, 118, 125, 132, 138, 145, 152, 160, 167, 175, 182, 188, 195, 201, 208, 213, 219, 224, 230, 235, 241, 250, 260]
#[6.0, 17.0, 27.0, 37.0, 47.0, 57.0, 67.0, 77.0, 87.0, 97.0, 107.5, 119.0, 131.5, 145.0, 159.5, 175.0, 191.5, 209.0, 228.0, 249.0, 272.0, 297.0, 324.0, 353.0, 384.0, 417.5, 454.0, 493.5, 536.5, 583.5, 634.5, 690.0, 750.0, 814.0, 882.5, 955.5, 1033.5, 1117.5, 1206.5, 1300.5, 1401.0, 1508.5, 1623.0, 1744.5, 1873.0, 2008.0, 2149.5, 2298.0, 2454.0, 2617.5, 2788.5, 2967.0, 3152.0, 3343.5, 3541.5, 3746.0, 3956.5, 4172.5, 4394.0, 4621.0, 4853.5, 5091.5, 5337.0, 5592.0]