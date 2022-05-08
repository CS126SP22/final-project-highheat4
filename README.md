## Animal Simulation: Natural Selection Demo

by Ayan Bhowmick for UIUC CS126


![image1](/animal_pictures/begin.png)

This is the first stage of the simulation, where vegetation is spawning in and animals are randomly generating over time. However, due to the low concentration of food, most animals will not survive past this stage.

![image2](/animal_pictures/middle.png)

During the second stage, animals are able to find food and the most successful animals of the randomly generated animals can survive long enough to reproduce.

![image3](/animal_pictures/end.png)

In the final stage, a few species of animals have been generated with close to ideal sets of genes. These animals have survived long enough to eat food and propagate, making these few species dominant in the simulation. You can see the gene values of some of these animals on the bottom left through the status screen.

## What is it?
This project is an animal simulator app where the fittest animals survive. Animals must eat food to replenish their energy and animals that run out of energy or food will die out. Animals randomly generate at the start of the program until a certain animal limit is reached. Animals that have eaten food and survived long enough will reproduce. You can see the stats of any animal by clicking on it or near it. Animals from the same family will have the same color.

## How do you use it?
You must have CLion and Cinder in order to run this project.
CLion and Cinder must be installed according to the instructions on its website. Once the two are installed, create a folder called my-projects  within the Cinder folder. Move this folder into the my-projects folder. After this is done, make sure to load the provided CMakeLists and you are ready to run!
To run the program, simply press the green play button on the top right corner and the simulation will run (after installing CLion). When you are done watching the simulation, click the red square bottom on the top right to stop it. During the simulation, click near an animal you want to see the status of and the status will be displayed.
