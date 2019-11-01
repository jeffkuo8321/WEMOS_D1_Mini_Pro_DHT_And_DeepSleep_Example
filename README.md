# WEMOS_D1_Mini_Pro_DHT_And_DeepSleep_Example
演示如何使用wemos d1 mini pro(後述為DMP) 透過 DHT 11模組取得即時的溫溼度，並在取得資料後進入深度睡眠模式(本例取完資料後每30秒醒一次).
本例使用DMP的 D8接腳當成控制DHT11電源的控制接腳，避免直接當DMP的3.3V或5V接到DHT11時，當DMP進入深度睡眠模式後還會一直耗電。
DMP的D6接腳則用來當DHT11的資料接收接腳。
以上的接腳可在原始碼中直接修改成想要的接腳。
