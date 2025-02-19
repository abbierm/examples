import httpx

r = httpx.get("https://api.openf1.org/v1/drivers")

try:
    drivers = r.json()
except httpx.HTTPError as exe:
    print(exe)


unique_drivers = set()
for driver in drivers:
    unique_drivers.add((driver['full_name'].upper(), driver['driver_number']))



with open("f1drivers.txt", "w") as f:
    for d in unique_drivers:
        f.write(f"{d[0]},{d[1]}\n")