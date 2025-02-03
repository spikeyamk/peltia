# Peltia To Do List

## peltia
- [ ] Integrate semantic versioning
- [ ] Hide everything under `peltia` namespace
- [ ] Define public API
- [ ] Change `ENABLE_DOCS`, `ENABLE_ADMIN`, to have `PELTIA_*` prefix
- [ ] Add `peltia_*` prefix to all
- [ ] Add optional `peltia_fw` target into CMake build system
- [ ] Add checks for pre-existing dependency targets
- [ ] Create first tag release with `CMAKE_BUILD_TYPE=Release`
- [ ] Use bitint, sevseg_char literals in the whole codebase
- [ ] Create public `peltia` with `add_library(peltia INTERFACE)` target, `peltia_fw`, `peltia_test`, `peltia_admin`, `peltia_docs` targets
- [ ] Start using `OpenOCD` instead of `STM32_Programmer_CLI`
- [ ] Rewrite the build system without globbing for files
- [ ] Remove dead code blocks
- [ ] create `peltia` public target
- [ ] use `deps` with `if(NOT TARGET...)` checks

## admin
- [ ] Charts drawing optimization
- [ ] Enable Control periodic timer
- [ ] Split PID::i into PID::i_static and PID::i_fuzzy
- [ ] Implement Transceiver state machine
- [ ] Enable logging to Console
- [ ] Add `About` to `Help` with semantic versioning, LICENSE, dependencies etc.
- [ ] Add `Docs` link to `Help`
- [ ] Enable fw version checking after `magic::results::Connect` arrives
- [ ] Programmatically call `AttachConsole` for Windows `CMAKE_BUILD_TYPE=Release` version
- [ ] Enable simultaneous calls to Transceiver from different `magic::commands` sources
- [ ] Enable temperature remote control through serial port
- [ ] Create CLI wrapper with `magic::commands::ResetToOTA`

## common
- [ ] Consider renaming to `public`?

### magic
- [ ] Split PID::i into PID::i_static and PID::i_fuzzy
- [ ] Introduce new `results::Log` without pair equivalent in `commands`
- [ ] Consider creating `results::ReadTempCtl::Periodic`
- [ ] Create `commands::RemoteControl`, `results::RemoteControl` pair
- [ ] Create `commands::ResetToOTA`, `results::ResetToOTA` pair
- [ ] Build as `INTERFACE` in CMake
- [ ] Create `Celsius` type
- [ ] Add polynomial temperature calculation for `MAX31865::RTD`
- [ ] Fix notation for Celsius in `SHT31::TempHum`
- [ ] Consider using ASCII `0x32` invisible space character for logging

## fw
- [ ] Create `peltia_bootloader`, `peltia_app` targets for flashing

### actu
- [ ] `fan` 1 kHz PWM and `fan::fb` adjustment

### bksram
- [ ] `test` bug fix
- [ ] `ErrorCodes` registry cleanup

### comm
- [ ] `rs232_uart` replicate into `usb_uart`
- [ ] redirect `stdout` to both `rs232_uart` and `usb_uart`
- [ ] move `rs232_uart::{Sempahore|SempahoreBase}` somewhere else

### core
- [ ] interrupt and exception handlers

### panel
#### button
- [ ] functions rename
- [ ] turn on, turn off, forward, back functionality
- [ ] debounce

#### sevseg
##### common
- [ ] get rid of magic numbers
- [ ] create `SevsegString` type with literals
##### green_yellow
- [ ] move `MAX6594` driver out, make it generic
- [ ] support setting intensity for individual digits
- [ ] stop using `HAL_MAX_DELAY` for SPI transmissions
##### white
- [ ] fix blinking using hardware or software timer or higher priority task with preemption scheduling policy

### sens
#### max31865
- [ ] fix `Transceiver` init function
- [ ] remove unnecessary state
- [ ] remove semaphore from `Extension`
- [ ] stop using `HAL_MAX_DELAY` for SPI transmissions
#### sht31
- [ ] one shot measurements
- [ ] stop using `HAL_MAX_DELAY` for I2C transmissions

### tasks
- [ ] `osThreadNew` returning `void*` investigation
- [ ] create `Semaphore` type
- [ ] create `Queue` type
- [ ] consider using `boost::hana` for template string
#### Panel
- [ ] state machine rewrite
- [ ] `Property` rewrite
- [ ] enable `Panel::AlgoProperty`
- [ ] disallow `FanSpeedPercentage` property to be set lower than `30` or similar value

#### RS232_UART
- [ ] `USB_UART` replicate from `RS232_UART`
- [ ] disallow simultaneous connections on `USB_UART` and `RS232_UART`
- [ ] rename into `Comm`
- [ ] enable `magic::commmands::RemoteCtl`

#### SenserKiller
- [ ] rewrite in functional style with `SenserKiller::{Test|Tester}`
- [ ] cleanup fail error codes
- [ ] `worker` use one shot measurement for SHT31
- [ ] consider creating another state machine for managing MAX31865, SHT31 and fan jobs or split `SenserKiller` into multiple tasks

#### SevsegWhite
- [ ] optimization for preemptive scheduling policy

#### TempCtl
- [ ] `Algorithm` remove dependency on `PID` type
- [ ] `PID::reset` logic
- [ ] implement following `Algorithm`'s: PBIN, P, PI, PID, PIDFZ, TUNE, DRY
- [ ] disable DRY `Algorithm` in `CMAKE_BUILD_TYPE=Release` build

## On Hold

- [ ] PLACEHOLDER

## Done ✓

- [x] PLACEHOLDER