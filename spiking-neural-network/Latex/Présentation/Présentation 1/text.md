Good morning teachers, 
Today we are going to present you our project, which is a project related to neural networks and more specifically spiking neural networks. In our case, we decided to focus on implementing a spiking neural network for audio classification.
We want to be able to classify audio signals into different categories, such as speech, music, noise, dog barking, etc.
We also want to compare the results with traditional neural networks
(- Implement a spiking neural network in a real-time application)

In order to show you the ins and outs of our project, we will first give you a brief overview of what spiking neural networks are, how they differ from traditional neural networks, and how they basically work.
Then we will introduce you to the dataset we are currently using for our project, what we have done to make it usable for our project and how we are now using it.
Finally, we will show you the progress and results we have achieved so far, and what we plan to do to improve our project in the near future.

... 

Now let us talk about the data we chose to use for our project.

At the beginning, and after some research, we knew that spiking neural networks are a type of neural network that consume less energy than traditional neural networks, but they can be much more complex to implement and train. Therefore, we decided to focus our attention on a type of data that requires less processing power and memory than, for example, images, but still retains the advantage of being potentially adaptable to real-time classification.
This lead us to choose audio signals as our data type.

Audio signals are abundant throughout the internet and specifically on YouTube, which is where we got our dataset from.

The Dataset we decided to use is called The Google AudioSet Dataset. It is a large-scale dataset of annotated audio events, it is mainly used for audio event detection and multi-classification (which fits our project perfectly).
It is also good to know that some ANN models have already been trained on parts this dataset and that its data type have already been used to pre-train other kinds of neural networks models. Models just like those:


Working with this dataset, and by that i mean collecting, formatting adapting and cleaning the data of this dataset turned out to be a bit more challenging than we expected.
We ended up:
- Modify a pre-existing python script to download, format and segment the data using parallel processing.
- Ensure that the output of the script is usable for our project.
- Clean the data from unwanted audio signals.


To conclude, now that we have a usable and pretty much balanced dataset as well as the basic knowledge for encoding and decoding audio signals into spikes, we can focus on some points of improvement for our project: 
- Finishing the implementation of the spiking neural network.
- Implementing the pre-trained traditional neural network for comparison.


