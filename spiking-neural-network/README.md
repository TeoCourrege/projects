The GitHub is structured as follows:

- `README.md`: this file
- `Latex`: contains the LaTeX source code for the paper
- `Code`: contains the pieces of code

In the code part, we have : 
- `Dataset`: contains the code used create and filter the dataset
- `Models`: contains some models used in the paper (not all for technical reasons)
- `Training scripts`: contains the scripts used to train the models (used on Kaggle mainly)
- `Test models`: contains the scripts used to test the models
- `Audio Reconstruction`: contains the scripts used to reconstruct the audio from spiking mfcc

In order to test the models, you would need to download the dataset and change the paths associated to each notebook as well as the paths to the models (variable ```PATH```).

Also, we recommend to use ```Kaggle```as some operations like the mfcc transform or even trying out the model can be quite heavy for a local machine. The only notebooks that would be simple to run on a local machine are the ```snn-mnist.ipynb``` and the ```Audio_Reconstruction.ipynb```.

Links to Kaggles : 

- ```snn-dataset``` : https://www.kaggle.com/code/loaigandeel/snn-dataset
- ```snn-mnist``` : https://www.kaggle.com/code/loaigandeel/snn-mnist
- ```ann-models``` : https://www.kaggle.com/code/loaigandeel/simple-model
- ```loading_csnn``` : https://www.kaggle.com/code/loaigandeel/loading-csnn-20-n-mfcc-raw-data
