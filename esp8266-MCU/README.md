# Configuration
## MPU

- LPF 	  4

*          |   ACCELEROMETER    |           GYROSCOPE
* DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
* ---------+-----------+--------+-----------+--------+-------------
* 0        | 260Hz     | 0ms    | 256Hz     | 0.98ms | 8kHz
* 1        | 184Hz     | 2.0ms  | 188Hz     | 1.9ms  | 1kHz
* 2        | 94Hz      | 3.0ms  | 98Hz      | 2.8ms  | 1kHz
* 3        | 44Hz      | 4.9ms  | 42Hz      | 4.8ms  | 1kHz
* 4        | 21Hz      | 8.5ms  | 20Hz      | 8.3ms  | 1kHz
* 5        | 10Hz      | 13.8ms | 10Hz      | 13.4ms | 1kHz
* 6        | 5Hz       | 19.0ms | 5Hz       | 18.6ms | 1kHz
* 7        |   -- Reserved --   |   -- Reserved --   | Reserved

- HPF 		1

* ACCEL_HPF | Filter Mode | Cut-off Frequency
* ----------+-------------+------------------
* 0         | Reset       | None
* 1         | On          | 5Hz
* 2         | On          | 2.5Hz
* 3         | On          | 1.25Hz
* 4         | On          | 0.63Hz
* 7         | Hold        | None

- GYRO_RNG 	2

* 0 = +/- 250 degrees/sec
* 1 = +/- 500 degrees/sec
* 2 = +/- 1000 degrees/sec
* 3 = +/- 2000 degrees/sec

- ACC_RNG 	3
* 0 = +/- 2g
* 1 = +/- 4g
* 2 = +/- 8g
* 3 = +/- 16g

- MOT_THRESHOLD 	5				LSB = 1 mg
- MOT_DUR			10				LSB = 1 ms

- MOT_DECREMENT	1		
			
* FF_COUNT | Counter Decrement
 * ---------+------------------
 * 0        | Reset
 * 1        | 1
 * 2        | 2
 * 3        | 4
 
- INT_MODE		1					push-pull / open-drain
- INT_LATCH		1					50 us pulse / active 
- INT_EN		1					enable interrupt
- LATCH_CLR		0					clear by read status / clear by read any

- FF_EN			0					enable free fall interrupt
- MOT_EN		1					enable motion interrupt
- ZERO_EN		0					enable zero motion interrupt
- FIFO_EN		0					enable buffer overflow interrupt
- MASTER_EN		0					enable master mode 
- RDY_EN		0					enable data ready interrupt