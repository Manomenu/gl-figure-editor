Description  
---
Window application written in C++/OpenGL that allows user to create figures and edit them.

Features  
---
- create figure by clicking on screen (click on first dot to close end figure creation)
- move figure by dragging a space with created figure
- edit figure by dragging its edges
- delete figures

Optimalization
---
- created frame buffer for storing data in each pixes with figures that cover that pixel (grants O(1) screen click processing)
