## LICENSE PLATE DETECTION

## MOTIVATION

Due to a significant rise in the number of vehicles these days, the number of incidents involving
stealing of vehicles, traffic rule violation and even accidents have increased. The License Plate
Detection plays a significant role in all these scenarios and can also be used for numerous
applications such as automatic toll collection, traffic law enforcement, parking lot access control
and road traffic monitoring. This project aims at reading the vehicle registration plate so that the
data extracted from the plate can be stored and used for the above mentioned applications. In
This project we use connected component analysis, segmentation and machine learning for
character detection and recognition.

## METHODOLOGY

1. This project is based on the common pattern matching technique for the recognition of a single
   font and a fixed size character. 
2. We first determine the region of interest i.e the license plate using
   assumptions on the characteristics of the license plate. And then we use machine learning
   classifiers to compare common patterns for fixed size letters obtained using segmentation
   performed on the license plate. 
3. However, to achieve good performance, large amounts of
  samples are needed. We have used the scikit-image, an image processing package for python
  and scikit-learn, a machine learning package for python. The algorithm we have followed is as
  shown below:
  
<img src="/algorithm.png" width="30%">
  
  
  ## TOOLS
  Python, sci-kit learn, sci-kit image, Linux, GitHub.
