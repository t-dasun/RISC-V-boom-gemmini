# Chipyard Basics and Simulation Notes

This note summarizes the key concepts of **Chipyard**, how hardware is generated, where files are located, and how to run simulations and collect waveforms.

---

## 1. Chipyard Philosophy

* **Traditional flow:** write separate Verilog files for each CPU variant (single-core, dual-core, 32-bit, 64-bit, etc.).
* **Chipyard flow:**

  * Hardware is described in **Chisel** (a Scala-based hardware construction language).
  * Different **configurations** are written in Scala (`Config` classes).
  * Chisel elaborates the design → FIRRTL → Verilog.
  * Verilog is generated automatically for the specified configuration.

This avoids duplication and makes it easy to explore different architectures.

---

## 2. Configurations

* Defined in:

  ```
  chipyard/generators/chipyard/src/main/scala/config/
  ```
* Examples:

  * **RocketConfig** → 1 Rocket core, 64-bit, default caches/memory.
  * **SmallBoomConfig** → 1 small BOOM core.
  * **DualRocketConfig** → 2 Rocket cores.
  * Others: configs for Gemmini, Hwacha, vector units, etc.

Example definition:

```scala
class RocketConfig extends Config(
  new chipyard.config.WithNBigCores(1) ++
  new freechips.rocketchip.system.BaseConfig
)
```

---

## 3. Building Hardware

* Build a specific configuration:

  ```bash
  cd chipyard/sims/verilator/
  make clean # For fresh build
  
  make CONFIG=RocketConfig
  ```
* This generates Verilog for a **Rocket-based SoC**.
* For BOOM:

  ```bash
  make CONFIG=SmallBoomConfig
  ```

Generated Verilog is located at:

```
chipyard/sims/verilator/generated-src/chipyard.TestHarness.<CONFIG>/
```

---

## 4. Simulation with Verilator

### Build simulator:

```bash
cd sims/verilator
make CONFIG=RocketConfig
```

* Produces binary:

  ```
  ./simulator-chipyard-RocketConfig
  ```

### Run a binary:

Two options (equivalent once the simulator is built):

1. **Makefile wrapper**:

   ```bash
   make run-binary CONFIG=RocketConfig BINARY=../../tests/hello.riscv
   ```

2. **Direct run**:

   ```bash
   ./simulator-chipyard-RocketConfig ../../tests/hello.riscv
   ```

Both run the program on the generated hardware.

---

## 5. RISC-V Toolchain

* Installed in Chipyard’s Conda environment:

  ```
  /chipyard/.conda-env/riscv-tools/riscv64-unknown-elf/bin
  ```
* Compile programs:

  ```bash
  riscv64-unknown-elf-gcc hello.c -o hello.riscv
  ```

---

## 6. Running ISA Tests

* Precompiled binaries live in:

  ```
  $RISCV/riscv64-unknown-elf/share/riscv-tests/isa/
  ```
* Example:

  ```bash
  make run-binary CONFIG=RocketConfig BINARY=$RISCV/riscv64-unknown-elf/share/riscv-tests/isa/rv64ui-p-simple

  make run-binary  BINARY=$RISCV/riscv64-unknown-elf/share/riscv-tests/isa/rv64ui-p-simple # When config is already done
  ```

  or

  ```bash
  ./simulator-chipyard-RocketConfig \
    $RISCV/riscv64-unknown-elf/share/riscv-tests/isa/rv64ui-p-simple
  ```

These tests verify instruction correctness.

---

## 7. Waveform (VCD/FST) Generation


Output:
   * cd `sims/verilator/output/chipyard.harness.TestHarness.RocketConfig`
   * Produces `rv64ui-p-simple.vcd` (or `.fst`) file in `sims/verilator/`.
   * View with GTKWave:

     ```bash
     gtkwave rv64ui-p-simple.vcd
     ```

This shows hardware signals (clocks, pipeline stages, memory buses) as the program executes.

---

## 8. +dramsim Option

* **Without `+dramsim`:**

  * Uses a simple, instant memory model.
  * Fast, good for correctness testing.

* **With `+dramsim`:**

  * Uses DRAMSim2 (cycle-accurate DRAM timing simulator).
  * Models real DRAM latency, banks, refresh, etc.
  * Slower, but useful for performance analysis.

Example:

```bash
./simulator-chipyard-RocketConfig +dramsim hello.riscv
```

---

## 9. Summary Workflow

1. Pick a config (`RocketConfig`, `SmallBoomConfig`, etc.).
2. Build simulator:

   ```bash
   make CONFIG=RocketConfig
   ```
3. Compile program with `riscv64-unknown-elf-gcc`.
4. Run simulation:

   ```bash
   ./simulator-chipyard-RocketConfig prog.riscv
   ```


---
