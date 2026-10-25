CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I../Platform/Inc -I../Devices/Inc
SRC = fake_bus.c test_mpu6050.c ../Devices/Src/mpu6050.c

test_runner: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: test_runner
	./test_runner

clean:
	rm -f test_runner