# Project Title: COMP2811 UI Final Project Coursework

## Our Team : New Group 40
In alphabetical order, name and student ID:

- Alexander Del Brocco | 201-492-689
- Thomas Onions        | 201-710-138
- Callum Soleit        | Not Present at Submission
- Kim Smith            | Not Present at Submission
- Zhi Qing Cheng       | Not Present at Submission

## Overview
This application is designed to monitor and analyse water quality data, with a focus on pollutant tracking and compliance with safety standards. It was developed using **C++/Qt6** with a modular and user-friendly interface that adapts to changes in locale for basic internationalisation.

It has working data visualisations of pollutant overviews, persistant pollutants and a compliance table

## Set-up Instructions

### Prerequisites
- **C++17** or higher
- **Qt6** libraries, including:
    - **QtWidgets**
    - **QtCharts**
    - **QPainter**
    - **QColor**
    - **QGridLayout**
    - **QPushButtons**

### Installation and Setup
1. **Extract the Starter Code**: 
 - Unzip the provided starter code package to a working directory.
2. **Build the Project**:
    - Create a `build` directory:
      ```bash
      mkdir build
      ```
    - Compile and Run the project:
      ```bash
        run.sh
      ```

## File Structure

codebase
- build
- hydromodel
- qtApp
- data
- CMakeLists.txt
- main.cpp
- run.sh
- README.md

### Build
The build folder contains the construction and executible of the application 
for now, as the application hasn't finished development. Despite the executible 
being located here, the primary way to run the program is "run.sh", which 
recompiles the code so the newest version is created, especially if it's on a 
different operating system.

### hydromodel
The hydromodel is the object oriented approach to the solution, modifying the 
previous "quaketool" code and configuring it to contain data from a formatted 
CSV file, setting the logical ground work. Inside it are:
- Hydromodel.hpp/cpp ~ Contains a Hydroset, and data functions
- Hydroset.hpp/cpp  ~ Contains a Waterbody Vector, which it indexes
- Waterbody.hpp/cpp ~ Contains fields for each row
- csv.hpp ~ Imported CSV handler

### qtApp
The qtApp directory contains the working pages/widgets of the qt application.
You should be forewarned that the code quality is poor and uncommented, as 
these were foresaken to achieve some demostraightable working product.
Each application page it's own set of files, represented by:
- dashboard.hpp/cpp ~ The main opening window when the user opens the app
- pollutant-overview.hpp/cpp
- persistent-pollutants.hpp/cpp
- enviroment-litter.hpp/cpp
- datapage.hpp/cpp ~ the compliance dashboard, modified datapage
- stats.hpp/cpp ~ This isn't a page, it's for data handling

### data
This directory is primarily for containing the CSV that the computer will read

### run.sh
This is the main file for compilation and running of the program, which
uses a bash script combined with the CMakeLists.txt to generate an 
executible in the build folder.

## Known Issues

- Code desperately needs modularisation and commenting 

- Dashboard sizes correctly, but does not resize correctly

- Time Series graph in Enviromental Litter doesn't always load data correctly

- XAxis in most data visualisations are too big to comprehend

- Data visualisations have parameters hardcoded in, not inputtable by avg user

- Data Axis Scope is hardcoded in, and doesn't adjust depending on data

- All pages are visible on nav bar and dashboard but aren't implemented
