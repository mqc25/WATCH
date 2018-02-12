# Configuration
## MPU

- **LPF**

<table>
  <tr>
    <th colspan="3" align="center">ACCELEROMETER</th>
    <th colspan="3" align="center">GYROSCOPE</th>
  </tr>
  <tr>
    <th align="center">DLPF_CFG</th>
    <th align="center">Bandwidth</th>
	<th align="center">Delay</th>
	<th align="center">Bandwidth</th>
	<th align="center">Delay</th>
	<th align="center">Sample Rate</th>
  </tr>
  <tr>
    <td align="right">0</td>
    <td align="right">260Hz </td>
    <td align="right">0ms</td>
	<td align="right">256Hz</td>
    <td align="right">0.98ms </td>
    <td align="right">8kHz</td>
  </tr>
  <tr>
    <td align="right">1</td>
    <td align="right">184Hz </td>
    <td align="right">2.0ms</td>
	<td align="right">188Hz</td>
    <td align="right">1.9ms </td>
    <td align="right">1kHz</td>
  </tr>
  <tr>
    <td align="right">2</td>
    <td align="right">94Hz </td>
    <td align="right">3.0ms</td>
	<td align="right">98Hz</td>
    <td align="right">2.8ms </td>
    <td align="right">1kHz</td>
  </tr>
  <tr>
    <td align="right">3</td>
    <td align="right">44Hz </td>
    <td align="right">4.9ms</td>
	<td align="right">42Hz</td>
    <td align="right">4.8ms </td>
    <td align="right">1kHz</td>
  </tr>
   <tr>
    <td align="right">4</td>
    <td align="right">21Hz </td>
    <td align="right">8.5ms</td>
	<td align="right">20Hz</td>
    <td align="right">8.3ms </td>
    <td align="right">1kHz</td>
  </tr>
  <tr>
    <td align="right">5</td>
    <td align="right">10Hz </td>
    <td align="right">13.8ms</td>
	<td align="right">10Hz</td>
    <td align="right">13.4ms </td>
    <td align="right">1kHz</td>
  </tr>
  <tr>
    <td align="right">6</td>
    <td align="right">5Hz </td>
    <td align="right">19.0ms</td>
	<td align="right">5Hz</td>
    <td align="right">18.6ms </td>
    <td align="right">1kHz</td>
  </tr>
  <tr>
    <td align="right">7</td>
    <td align="center" colspan="2">Reserved </td>
    <td align="center" colspan="3">Reserved </td>
  </tr>
</table>

- **HPF** 	

 ACCEL_HPF | Filter Mode | Cut-off Frequency
 ---------:|------------:|----------------:
 0         | Reset       | None
 1         | On          | 5Hz
 2         | On          | 2.5Hz
 3         | On          | 1.25Hz
 4         | On          | 0.63Hz
 7         | Hold        | None

- **GYRO_RNG** 	

Value	| GYROSCOPE RANGE
--------|--------------------
0 		| +/- 250 degrees/sec
1 		| +/- 500 degrees/sec
2 		| +/- 1000 degrees/sec
3 		| +/- 2000 degrees/sec
	
- **ACC_RNG**

Value	| ACCELEROMETER RANGE
--------|--------------------
0 		| +/- 2g
1 		| +/- 4g
2 		| +/- 8g
3 		| +/- 16g

- **MOT_THRESHOLD:** LSB = 1 mg

- **MOT_DUR:** LSB = 1 ms

- **MOT_DECREMENT:** Decrement per sub-threshold sample		
			
FF_COUNT | Counter Decrement
---------|------------------
0        | Reset
1        | 1
2        | 2
3        | 4
 
- **INT_MODE:**							push-pull / open-drain
- **INT_LATCH:**						50 us pulse / active 
- **LATCH_CLR:**						clear by read status / clear by read any

- **INT_EN:**							enable interrupt
- **FF_EN:**							enable free fall interrupt
- **MOT_EN:**							enable motion interrupt
- **ZERO_EN:**							enable zero motion interrupt
- **FIFO_EN:**							enable buffer overflow interrupt
- **MASTER_EN:**						enable master mode 
- **RDY_EN:**							enable data ready interrupt