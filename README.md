# A Beginner's Guide to Building a RISC-V SoC with Chipyard

This guide outlines the fundamental steps to get started with designing a custom System-on-Chip (SoC) using the Chipyard framework, from understanding the basics to simulating a complete system.

---

## Step 1: Learn the "Language" - The RISC-V ISA 📜

Before building a house, you need to understand the blueprint. The RISC-V Instruction Set Architecture (ISA) is the blueprint for the cores you'll be using. You don't need to be an expert, but spend a little time learning the basics:

* What are **registers**?
* What do simple instructions like `add`, `lw` (load word), and `sw` (store word) do?

This foundation will make everything else make much more sense.

---

## Step 2: Set Up Your "Factory" - Install Chipyard 🏭

Your main tool is Chipyard. The most important first step is to get the development environment set up correctly on a Linux machine. Follow the official Chipyard documentation very carefully. This can be the hardest part, so take your time.

[Link to the official Chipyard setup documentation](https://chipyard.readthedocs.io/en/stable/Chipyard-Basics/Initial-Repo-Setup.html)

---

## Step 3: Your "Hello, World!" - Simulate a Default Chip ⚙️

Once Chipyard is installed, your first goal is not to build something new, but to successfully build and simulate one of the default designs. A great starting point is the `RocketConfig`.

You will run a command that tells Chipyard to:

* Generate the hardware design (in Verilog).
* Compile that design into a C++ program using Verilator (the default RTL simulator).
* Run a simple test program (like "hello world") on your simulated chip.

This is the most critical step. It confirms your setup works and teaches you the basic workflow. All of this happens **without QEMU**. You are directly simulating the hardware you just created.

---

## Step 4: Make Your First Modification 🛠️

Now you can start customizing. Instead of building the default `RocketConfig`, try building the `BoomConfig`. This swaps the simple, in-order Rocket core for the more powerful, out-of-order BOOM core.

Compile and run the same tests. This teaches you how to change the configuration of your SoC, which is the main way you design things in Chipyard.

---

## Step 5: Add the Accelerator (Gemmini) 🧠

Once you're comfortable building SoCs with different cores, the next step is to add your Gemmini accelerator. You'll edit the configuration file to include the Gemmini generator.

Then, you can run the special tests included with Gemmini to see the accelerator in action. These tests will run on your simulated BOOM core and send special commands to your simulated Gemmini accelerator to perform matrix multiplications.

---

## Step 6: The Final Step - Full-System Simulation with QEMU 🖥️

After you have successfully built and tested a chip with a core and an accelerator using Verilator, now you can bring in QEMU.