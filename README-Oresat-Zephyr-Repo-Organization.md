# Zephyr Firmware Plan for Oresat 1.0

**DRAFT 2**

- Introduction
- Repositories
- Repository Layout
- Filesystem Layout
- Firmware Team Roles
  - PR Management
- Workflows
  - Card Application Workflow
    - Tasks
  - Oresat Integrator Workflow
    - Structural components
    - Tasks
  - Oresat Release Workflow
- Build and Configuration System
  - West Multirepository Management Tool
  - CMake Meta-build Tool
  - Zephyr Toolchain
  - KConfig Software Configuration System
  - Device Tree Hardware Configuration System

---

## Introduction

This document describes a proposal for a new arrangement of Git repositories that contain logically separate portions of the Zephyr firmware applications that target the various cards on the Oresat bus, aimed at use on Oresat 1 and later. It also describes how they are connected together through west manifests and submanifests with common Oresat code as well as Zephyr and its support modules. Further, it explains the various roles within the team, gives a high level view of their workflows, and a high level view of the various tools.

A major goal is to reduce or eliminate the need for someone working on a specific portion of the full system to need to routinely have to modify anything outside of that portion's repository. Doing so requires them to create multiple pull requests which then need to be coordinated, which in the past has been a pain point within the team with a less granular system.

Users should be able to create a branch on a specific Oresat repo, work in that branch, test it, then create a pull request. Once their pull request is merged, anyone else will simply receive the new version whenever they do a *west update*.

---

## Repositories

Prior to adopting this plan officially for Oresat >= 1.0, the following public github repositories were in my personal github account and named slightly differently ([github.com/plskeggs](https://github.com/plskeggs)).

Now, all but **oresat-mcxn947-demo** and **oresat-mcxn947-protoboard** are in the Oresat github account ([github.com/oresat](https://github.com/oresat)). These will eventually be merged into the **oresat-template-app**, with additional support for other boards, such as the ST Nucleo-F091RC dev kit.

The **oresat-zephyr-common** repo below is now a branch ***zephyr*** of the old oresat-firmware repo. Eventually the old master branch will be renamed (essentially archived) and replaced by the zephyr branch.

- [Oresat-adcs-app](https://github.com/oresat/oresat-adcs-app)  
  Placeholder
- [Oresat-battery-app](https://github.com/oresat/oresat-battery-app)  
  Port from the previous Oresat zephyr structure.
- [Oresat-solar-app](https://github.com/oresat/oresat-solar-app)  
  Placeholder
- [Oresat-template-app](https://github.com/oresat/oresat-template-app)  
  Prototype application, with a working example of using logging.
- [Oresat-mcxn947-demo](https://github.com/plskeggs/oresat-mcxn947-demo)  
  A working example of using various hardware in the MCXN.
- [Oresat-mcxn947-protoboard](https://github.com/plskeggs/oresat-mcxn947-protoboard)  
  Board files for the breakout board.
- [Oresat-firmware](https://github.com/oresat/oresat-firmware) → *moved here in **zephyr** branch from oresat-zephyr-common*  
  This is the central repository containing west.yml.

## Repository Organization

These repositories are broken down into the following major categories:

1. Oresat card applications, each in its own repository
   - a. ADCS
   - b. Battery
   - c. Solar
   - d. Template
   - e. MCXN (Breakout) Demo
   - f. **NOTE**: each card application can have a submanifest that enables additional Zephyr modules that are not in the common list inside the main Oresat west.yml
2. Oresat firmware *(in a branch called **zephyr**)*  
   This repository hooks everything together, holds common utility functions and libraries, as well as board files and device drivers. In the original Oresat Zephyr layout this was called **oresat-zephyr, which is now obsolete.**
   - a. Oresat board file definitions (device trees and Kconfig settings) – or perhaps just in the card application folders, though that seems limiting in other ways
   - b. Oresat device drivers – perhaps in the card application folders, but by centralizing them they can be reused by more than one card
   - c. Canopennode_v4 (unless we move back to v2, already part of Zephyr)  
     Zephyr is currently stuck at canopennode_v2, whereas *oresat-configs* was already upgraded to support canopennode_v4 for ChibiOS, so rather than backtrack, an Oresat volunteer ported Zephyr's canopennode_v2 interface code (canopennode.c, CO_driver.c) to v4
   - d. The main **west.yml** used when initializing a west workspace
   - e. satellite-specific sysbuild files which would combine MCUboot builds with an application build into a final flash image for that application's card; OTA images will also be built that do not include MCUboot but can instead be loaded by it
3. Zephyr and all of its dependent repositories
   - a. Zephyr itself, including Zephyr's **west.yml**
   - b. Zephyr-approved and integrated third-party modules as selected in the main west.yml above, as well as in the specific application's submanifest
   - c. MCUboot

---

## Filesystem Layout

A nice thing about west is that the west.yml file can place repos wherever you want inside its workspace. A west workspace is where the .west/ folder is. I chose shorter folder names rather than use the original full names so we can type less.

Below, the ⇐ characters indicate where **west** cloned each git repo listed above.

```
./
├── apps/
│   ├── adcs/ ⇐ https://github.com/oresat/oresat-adcs-app
│   ├── battery/ ⇐ https://github.com/oresat/oresat-battery-app
│   │   ├── src/
│   │   │   └── main.c
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   ├── od.yaml
│   │   ├── prj.conf
│   │   ├── README.md
│   │   └── sample.yaml
│   ├── solar/ ⇐ https://github.com/oresat/oresat-solar-app
│   ├── mcxn947-demo = https://github.com/plskeggs/oresat-mcxn947-demo
│   │   └── boards
│   │       └── mcxn947_protocard = https://github.com/plskeggs/oresat-mcxn947-protocard
│   │           ├── board.c
│   │           ├── board.cmake
│   │           ├── board.yml
│   │           ├── CMakeLists.txt
│   │           ├── Kconfig
│   │           ├── Kconfig.defconfig
│   │           ├── Kconfig.mcxn947_protocard
│   │           ├── mcxn947_protocard.dtsi
│   │           ├── mcxn947_protocard.dtsi
│   │           ├── mcxn947_protocard_mcxn947_cpu0_defconfig
│   │           ├── mcxn947_protocard_mcxn947_cpu0.dts
│   │           ├── mcxn947_protocard_mcxn947_cpu0.dtsi
│   │           ├── mcxn947_protocard-pinctrl.dtsi
│   │           ├── mcxn947_protocard.yaml
│   │           └── README.md
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   ├── prj.conf
│   │   ├── README.md
│   │   ├── sample.yaml
│   │   └── src
│   │       ├── adc.c
│   │       ├── blink.c
│   │       ├── dac.c
│   │       ├── i2c_sensor.c
│   │       └── main.c
│   └── template/ ⇐ https://github.com/oresat/oresat-template-app
│       ├── src/
│       │   └── main.c
│       ├── submanifests/
│       │   └── example.yaml  = EXAMPLE TO PULL IN ANOTHER MODULE
│       ├── CMakeLists.txt
│       ├── Kconfig
│       ├── LICENSE
│       ├── prj.conf
│       └── README.md
├── common/ ⇐ https://github.com/oresat/oresat-firmware (zephyr branch)
│   ├── boards/
│   ├── drivers/
│   ├── lib/
│   │   ├── canopennode_v4/
│   │   │   ├── CANopenNode/ ⇐
│   │   │   ├── canopennode.c
│   │   │   ├── canopennode.h
│   │   │   ├── CMakeLists.txt
│   │   │   ├── CO_driver.c
│   │   │   ├── CO_driver_custom.h
│   │   │   ├── CO_driver_target.h
│   │   │   └── Kconfig
│   │   ├── util/
│   │   │   ├── board_sensors.c
│   │   │   ├── board_sensors.h
│   │   │   ├── CMakeLists.txt
│   │   │   ├── Kconfig
│   │   │   ├── od.yaml
│   │   │   └── oresat.h
│   │   ├── CMakeLists.txt
│   │   └── Kconfig
│   ├── zephyr/
│   │   └── module.yml
│   ├── CMakeLists.txt
│   ├── format_code.sh*
│   ├── Kconfig
│   ├── LICENSE
│   ├── od.yaml
│   ├── README.md
│   └── west.yml  = THIS IS OUR TOP-LEVEL west MANIFEST
├── modules/
│   ├── debug/ ⇐ repo links determined by west in Zephyr's *west.yml*
│   ├── hal/ ⇐ ""
│   └── lib/ ⇐ ""
└── zephyr/ ⇐ https://github.com/zephyrproject-rtos/zephyr
    ├── arch/
    ├── boards/
    ├── cmake/
    ├── doc/
    ├── drivers/
    ├── dts/
    ├── include/
    ├── kernel/
    ├── lib/
    ├── misc/
    ├── modules/
    ├── samples/
    ├── scripts/
    ├── share/
    ├── snippets/
    ├── soc/
    ├── submanifests/
    ├── subsys/
    ├── tests/
    ├── CMakeLists.txt
    ├── Kconfig
    ├── Kconfig.constants
    ├── Kconfig.zephyr
    ├── version.h.in
    ├── west.yml  = THIS IS ZEPHYR'S MANIFEST; OURS POINTS TO THIS
    └── zephyr-env.sh
```

---

## Firmware Team Roles

- Card application contributors
  - Role open to anyone at any level of skill
  - Work mostly limited to within a specific card application repository
- Device tree, board file, and device driver contributors
  - Ideally done in collaboration between avionics team, Zephyr specialists, and application contributors
  - Ideally uses best practices and similar styles
- Common repository contributors
  - Common code lead contributor
  - Other contributors as needed
  - Requires knowledge of west manifests, Zephyr drivers, board files, device trees, and configuration for Zephyr
- Zephyr integration specialists
  - Roles initially limited to those already possessing extensive Zephyr experience
  - Open to others after training
  - Responsible for maintaining all the manifests and submanifests, CMake files, and scripts
- Oresat test and integration specialists
  - I am guessing this would involve avionics folks, software developers, and firmware developers
- Oresat release manager
  - Responsible for tagging or branching repos and updating the common west.yml file so specific launch configurations can be easily rebuilt
  - Responsible for disseminating official build products for deployment on each card prior to launch
- Outside contributors

### PR Management

Not directly mentioned above is who is allowed to approve and who is allowed to merge pull requests.

There should be a balance between empowering contributors with making sure quality is acceptable. Code reviews are a good thing and valuable to gain experience with, but if the approver list is too short, the approvers become bottlenecks that hinder progress.

---

## Workflows

### Card Application Workflow

Our goal is to make this as painless as possible for students and new community volunteers to get started making meaningful contributions to firmware for specific cards.

- Simple and short instructions
- Everything preconfigured to just work
- Minimal prerequisite knowledge of Zephyr and the various tools

#### Tasks

1. Initial setup  
   Below is a summary.  
   See the [oresat-firmware zephyr README](https://github.com/oresat/oresat-firmware) for all details.
   - a. Install dependencies
   - b. Install Zephyr SDK (toolchain contains target device C compiler, linker, build tools)
   - c. Install west
   - d. initialize workspace
     ```
     $ west init…
     ```
     pull down source code
     ```
     $ west update
     ```
   - e. Install some more stuff
   - f. Do a test build, flash to target board, confirm it works

2. Work on changes to an app
   - a. On a fresh setup, check out the main branch of the app, since it will currently be pointing at a special branch *manifest-rev* with a detached git HEAD.
     ```
     ~/src/oresat/firmware$ cd apps/solar
     ~/src/oresat/firmware/apps/solar$ git branch
     * (HEAD detached at refs/heads/manifest-rev)
       Manifest-rev
     ~/src/oresat/firmware/apps/solar$ git fetch
     From https://github.com/oresat/oresat-solar-app
      * [new branch]      main       -> oresat/main
     ~/src/oresat/firmware/apps/solar$ git checkout main
     branch 'main' set up to track 'oresat/main'.
     Switched to a new branch 'main'
     ```
   - b. Create a new branch and switch to it, for example:
     ```
     $ git branch feature-optimize-control-loop
     $ git switch feature-optimize-control-loop
     ```
     Or simply:
     ```
     $ git checkout -b feature-optimize-control-loop
     ```
   - c. **Avoid doing another `west update` unless really needed** (see below)
   - d. Edit, test, debug, repeat
   - e. Document work done
     - i. README.md: for users of the app
     - ii. code comments: for future developers
     - iii. git commit messages: for developers to understand history of changes
     - iv. Slack: to alert others how your work might affect them
     - v. Google docs: for big picture overviews and detailed design info
   - f. Submit your pull request when ready for review (push to remote, etc.)
   - g. Make more changes based on review comments, if needed
   - h. Once merged to the main branch, delete your working branch
     ```
     $ git branch -d feature-optimize-control-loop
     ```
     Though some prefer to keep them for a while

3. Update to latest source code
   - a. Best to do when not in the middle of working on changes to existing code, because:
     - i. You were told that an important new release of our common code is required
     - ii. You report a problem in common code and a fix, usually by some other responsible party, is ready
   - b. When you are in the middle of things:
     - i. Confirm you are in an active branch, not a detached HEAD:
       ```
       $ git branch --show-current  NOTE: shows nothing when detached:
       $ git branch  NOTE: shows more, but easy to miss with a lot of branches:
       * (HEAD detached at e9c01d8)
         main
         Manifest-rev
       ```
     - ii. If not in an active branch, switch back to the branch your work is in
       ```
       $ git switch feature-optimize-control-loop
       ```
     - iii. Commit your changes locally to your branch  
       (usually no need to push up to remote)
       ```
       $ git add …
       $ git commit -m "commit message"
       ```
     - iv. Do *west update* and watch the log output – it will likely switch away from your branch, and tell you this, and give you directions how to switch back:
          ```
          $ west update
          === updating zephyr (zephyr):
          HEAD is now at b6aed5c505e kernel: dynamic: use 4k stack size for x86
          === updating oresat-template-app (apps/template):
          --- oresat-template-app: fetching, need revision main
          From https://github.com/oresat/oresat-template-app
           * branch            main       -> FETCH_HEAD
          HEAD is now at ac7502a ignore any path that starts with build
          === updating CANopenNode (common/lib/canopennode_v4/CANopenNode):
          HEAD is now at 58012aa Fix links
          === updating oresat-configs (oresat-configs):
          HEAD is now at 0a26511 fix pip install command error in readme
          === updating oresat-adcs-app (apps/adcs):
          --- oresat-adcs-app: fetching, need revision main
          From https://github.com/oresat/oresat-adcs-app
           * branch            main       -> FETCH_HEAD
          HEAD is now at eb51038 Initial commit
          === updating oresat-battery-app (apps/battery):
          --- oresat-app-battery: fetching, need revision main
          From https://github.com/oresat/oresat-battery-app
           * branch            main       -> FETCH_HEAD
          HEAD is now at e9c01d8 Initial commit
          WARNING: left behind oresat-battery-app branch
          "feature-optimize-control-loop"; to switch back to it (fast forward):
          git -C . checkout feature-optimize-control-loop
          === updating oresat-solar-app (apps/solar):
          --- oresat-solar-app: fetching, need revision main
          From https://github.com/oresat/oresat-solar-app
           * branch            main       -> FETCH_HEAD
          ```

---

### Oresat Integrator Workflow

Integrators implement and maintain the structures that hold the Oresat firmware project together. They document, explain, and support card application developers and others to perform their roles. They review pull requests against the common repositories as well as card application repositories when those pull requests propose changes to structural components. They understand, explain, and promote best practices.

#### Structural components

- west configuration files (west.yml) and submanifest files (foo.yaml)
- CMake files (CMakeLists.txt, foo.cmake, etc.)
- Kconfig files (Kconfig*, prj.conf)
- Device tree files (*.dts, *.dtsi)
- Scripts (usually Python)

#### Tasks

1. 

---

### Oresat Release Workflow

The Oresat release manager ensures that satellites leaving PSU for launch contain the correct firmware:

- That passes all automated and manual tests
- That testers and responsible parties agree the release contains the correct code
- That any one-time prelaunch configurations have been done to it (e.g., resetting statistics stored in non-volatile memory)
- That no uncommitted and untracked changes are made to launch code

They make sure:

- the firmware was tagged in git so it can be built again if required
- The other teams (avionics, logistics?, etc.) are informed

---

## Build and Configuration System

### West Multirepository Management Tool

The common repository README.md will contain a simple set of instructions for how to install the various required tools and then use **west** to populate the Oresat repos as well as Zephyr's.

West's main use is to combine specific commits from multiple repositories and their repository-specific west YAML files, into a cohesive arrangement of Git sandboxes within a Zephyr workspace. This ensures that each independent yet interrelated repository will be able to find any dependencies it may have, at the correct Git commit.

While not technically a build system, west has integrated extensions which provide easy ways to build and flash applications.

### CMake Meta-build Tool

The template application will have a starting example with comments about where users will need to make edits, with examples.

CMake is a meta-build tool which generates build configuration files for Make or Ninja build tools. The build tool then can build a binary image that can be programmed to a target device. CMake is cross platform, which allows it to work on a variety of host operating systems, by automatically finding toolchains for compiling and linking within prescribed locations, often set through operating system environment variables, then placing the host-os-specific filesystem locations in the build configurations as required.

CMake makes it easier than it used to be to build complex systems, which often required other complex and brittle tools and provided hard to follow instructions for users to get started.

### Zephyr Toolchain

The common repository README.md will contain instructions for downloading and installing the required toolchain.

### KConfig Software Configuration System

### Device Tree Hardware Configuration System


## TODO

### Doc Fixes

- Add missing branch in code block in west update example
- Add Python virtual environment instructions or break system packages
- Blinky outputs app_template to terminal by mistake (fixed in blink.c in apps/mcxn947-demo)
  Missed pointing out build products (Zephyr device tree) summarize all dts and kconfig (added to new section at end of doc)
  Added a subsection to the west section near the end, that explains manifest-rev


### On YouTube

- I said "repo" instead of just "name of remote" by mistake during the west manifest walk through
- Further explanation of Manifest-rev: it is intended to not conflict with any local branch name that user creates (see updated West section of Zephyr Repo Layout)
- Note that there is a Zephyr Project Discord channel: https://discord.com/invite/Ck7jw53nU2
