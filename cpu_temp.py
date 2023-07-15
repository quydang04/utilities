from raspc_notif import notif
from time import sleep
import subprocess


#Enter the User API Key you find in the RaspController app
sender = notif.Sender(apikey = "XrpdqP7238aAOGk1DsORCFhqz4R2-Vw6DENElh9RKNt3NKq3kGvgF8Q__9WsccGtei1CGeRA_")


#Infinite loop to continuously get data
while True:
	
	#Gets data once every 5 seconds
	sleep(5)
	
	#Gets the CPU temperature
	cpu_temp_str = subprocess.check_output(["cat", "/sys/class/thermal/thermal_zone0/temp"]).decode("utf-8").strip()
	cpu_temp = float(cpu_temp_str) / 1000
	
	#Check if the temperature exceeds a certain threshold
	if cpu_temp > 70:
		
		#Send notification to RaspController
		notif_message = "The CPU has reached the temperature of {0}°C".format(cpu_temp)
		notification = notif.Notification("Attention!", notif_message, high_priority = True)
		result = sender.send_notification(notification)
		
		#Check if the submission was successful
		if result.status == notif.Result.SUCCESS:
			print(result.message)
		else:
			print("ERROR: {0}".format(result.message))
			
		#Wait 6 minutes before sending a notification again
		if result.status != notif.Result.SOCKET_ERROR:
			sleep(60 * 6) 
