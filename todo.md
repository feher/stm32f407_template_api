Rename Util::Bits to Util::BitSpan
Rename Util::BitsRegister to Util::BitSpanArray
- TBitsEnum -> TIndexEnum

Convert to bitapi2:
- Current bitapi is too rigid
  - every peripheral is a different type (Tim2 vs Tim3)
  - cannot interchange peripherals of same class (Tim2 <--> Tim3)
- struct mapped to address
- want to be able to pass Timer (or other peripheral) to functions.
  - functions should not care what timer it is (Tim2, Tim3, etc)

Split up to libs
- circular_buffer
  - create tests that run on host?
  - unit/integration tests on device?
- active_objects
- bitapi
- drivers
