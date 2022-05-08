Week 1: added vegetation and general implementation of animals. This means that we can see vegetation grow on the screen when we press the play button. The vegetation grows every 60 frames and a new vegetation spawns in every 60 seconds up to a maximum capped number. The herbivore class is made but not yet fully implemented and unready to be spawned into our visual environment.

Week 2: finished adding herbivores and they can interact with vegetation by eating them. Essentially, herbivores are now able to be spawned into the visual environment and can interact with one another as well as with vegetation. The herbivore has multiple private factors, including energy and health. A herbivore has been coded to die once it runs out of energy or health. A herbivore can replenish energy by contacting some vegetation and eating it, capping restored energy by its max eat rate and vegetation size. The vegetation will shrink in size upon being eaten, and if it is fully consumed then the vegetation will disappear.

Week 3: implemented animal reproduction upon meeting survival criterion. The reproductive criterion have been set so that the herbivores must a) survive for a long period of time and b) eat some food. This is because upon testing, some species were able to survive for long periods of time due to low growth rates and reproduced despite having almost no food available. In other words, the herbivores were reproducing faster than they were dying despite the lack of any sustenance. Thus, some balance had to be added so that this does not occur. Another issue was that some herbivores grew much too large. This was fixed by increasing the energy cost ratio of size from radius to radius ^ 2 (as the actual size of the herbivore would be pi * radius ^ 2, this felt like a good way to calculate energy cost anyway). After this adjustment, the most successful herbivores had very low growth rates.  

Week 4: displayed status of nearest herbivore on-click. I found that there an issue since all children were spawning at radius 1. This means that the must successful type of species (the ones with low growth rates and health) would be able to survive even longer as a result of being born smaller. To balance this, children born from adult herbivores would spawn at whichever is greater between 1/10th the adult size and 1. To help people keep track of families better, all offspring of a herbivore would spawn with the EXACT same color as the parent. Lastly, I created a new folder for the animal statistics and allowed the herbivore statistics/status to be displayed through this class by clicking close to a herbivore of interest.