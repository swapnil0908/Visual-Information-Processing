
import os
import numpy as np
from sklearn.svm import SVC
from sklearn.model_selection import cross_val_score
from sklearn.externals import joblib
from skimage.io import imread
from skimage.filters import threshold_otsu

letters = [
           '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
           'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T',
           'U', 'V', 'W', 'X', 'Y', 'Z'
           ]

def train_letters(dict_train):
    imgs = []
    img_to = []
    for letter in letters:
        for i in range(10):
            img_path = os.path.join(dict_train, letter, letter + '_' + str(i) + '.jpg')
            imgrey = imread(img_path, as_grey=True)
            binary_image = imgrey < threshold_otsu(imgrey)
            
            flat_bin_image = binary_image.reshape(-1)
            imgs.append(flat_bin_image)
            img_to.append(letter)

return (np.array(imgs), np.array(img_to))

def cross_validation(model, num_of_fold, train_data, train_label):
    
    better = cross_val_score(model, train_data, train_label,
                             cv=num_of_fold)
        print("Cross Validation Result for ", str(num_of_fold), " -fold")
                             
    print(better * 100)


directory = os.path.dirname(os.path.realpath(__file__))

training_dir = os.path.join(directory, 'train')

imgs, img_to = train_letters(training_dir)

svc_mdl = SVC(kernel='linear', probability=True)

cross_validation(svc_mdl, 4, imgs, img_to)

svc_mdl.fit(imgs, img_to)

which_dir = os.path.join(directory, 'models/svc/')
if not os.path.exists(which_dir):
    os.makedirs(which_dir)
joblib.dump(svc_mdl, which_dir+'/svc.pkl')



