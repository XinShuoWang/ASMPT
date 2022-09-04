# Task Description
- Build a windows application (MFC framework preferred).
- Init the window with 4 graphic elements, each element has a value (1 to 4). It also should have other properties such as shape, color and size etc. Draw all elements in the window in a row with ascending order.
- User can insert elements into the row:
	- Insert to the beginning: new element’s value = original first element’s value – 1
	- Insert to the end: new element’s value = original last element’s value + 1
	- Insert to the middle: new element’s value = average of the neighboring element’s value
- User can delete elements of the row, all others remain the same
- The row should be auto aligned with equal space between each other

# Analysis
Specifically, the following technologies may be involved:
- Use of the MFC framework:
   - Use the MFC framework to draw and fill graphics, print numbers, clear the graphics that have been drawn by the window
   - Use the MFC framework to interact with the user and get user input
- Polymorphic features of C++: Since there are some common characteristics between graphics classes, a graphics base class `Shape` can be abstracted, and each subclass can implement its own Draw() method
- Smart pointers: We can use smart pointers instead of new/delete to manually manage memory
- Standard Template Library (STL): It will also involve the use of STL
- Mathematical calculation: Because the graphics are required to be automatically aligned, the coordinates of each graphic must be calculated every time
- Exception handling:
   - When the height of the newly inserted graphic by the user is greater than the height of the window, the graphic cannot be added at this time
   - When the sum of the width of all the graphics inserted by the user is greater than the width of the window, the graphics cannot continue to be added at this time
   - When the input ListBox isn't selected, the operation is invalid


# Implmentation
## Input module
The user needs to interact with the input module to submit the shape of the element to be inserted, the relative position of the reference object, the reference object, color, size and other information. I use ListBox to help user enter specific information. Of course, i can also use the TextBox for input, but in this case, the exception handling logic will become complicated. In order to focus on this task, the TextBox input method is not introduced.

## Render module
After the user completes the input, the rendering module needs to update the graphics of the window in time. The function provided by MFC is mainly used to draw the graphics, and several code snippets for drawing graphics are given below.

```
// Draw Rectangle
cdc->Rectangle(x - w / 2, y - h / 2, x + w / 2, y + h / 2);

// Draw Circle
cdc->Ellipse(x - r, y - r, x + r, y + r);

// Print
cdc->TextOutW(x, y, content);
```

## Intermediate data structure
I use `std::vector<std::shared_ptr<ASMPT::Shape>>`, `ASMPT::AddEventOption` and `ASMPT::DelEventOption` in order to reduce the coupling between the user input module and the rendering module. These data structures make the connection between the user input module and the rendering module, but do not confused, each module is only responsible for these intermediate data structures. The definition code snippet of the intermediate data structure is shown below:

```
/* 
 * This data structure is used as the interaction hub between the rendering module and the user module.
 * The rendering module renders according to this data structure, and the user module will operate this
 * data structure to achieve the purpose of adding or deleting.
 * 
 * Although using std::list may be more in line with the requirements,
 * in order to facilitate the subsequent use of the index to insert nodes directly,
 * I still use std::vector, and in the case of a small amount of data, there is almost 
 * no performance gap between std::vector and std::list.
 * 
 * The use of pointers is to facilitate the use of C++'s polymorphic features.
 * 
 * Using smart pointers can reduce the mental burden of memory management.
 */
std::vector<std::shared_ptr<ASMPT::Shape>> graphic_elements_;

// All operations of adding nodes will be recorded in this structure
ASMPT::AddEventOption insert_option_;

// All operations of deleting nodes will be recorded in this structure
ASMPT::DelEventOption delete_option_;
```


# Demonstrate
## Graphic User Interface
![interface display](https://user-images.githubusercontent.com/56379080/188304781-3384ea4a-643e-454a-ae30-24a014453bcc.png)

## Insert
### Insert at beginning
![insert_begin](https://user-images.githubusercontent.com/56379080/188308301-f51a7ab9-0156-44a2-9986-ce4a4caacb1b.gif)

### Insert at end
![insert_end](https://user-images.githubusercontent.com/56379080/188308323-887c0ef7-f61b-45a7-bcff-0f57e397419e.gif)

### Insert at middle
![insert_middle](https://user-images.githubusercontent.com/56379080/188308349-09c1d36c-50aa-42ef-a1d6-152e0d7505f6.gif)

### Insert until full
![insert_all](https://user-images.githubusercontent.com/56379080/188308394-e356cc3b-90cf-4536-85bb-01af56aaddf5.gif)

## Delete
![delete](https://user-images.githubusercontent.com/56379080/188308363-1e9bea9d-7ae0-4d0e-8935-eb26a21e58d1.gif)

# About Me
I have been engaged in research work related to database kernel, computer architecture, and storage during my graduate studies, so I am relatively proficient in using C/C++.
I have not been exposed to MFC programming before, but in this small task, I completed the task within two days with a good C++ foundation and strong learning and understanding ability.
