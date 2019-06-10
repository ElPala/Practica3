.PHONY: all serieleibniz serieleibniz_hilos serieleibniz_hilosprocesos serieleibniz_procesos clean
all: serieleibniz serieleibniz_hilos serieleibniz_hilosprocesos serieleibniz_procesos

serieleibniz: serieleibniz.c
		gcc -o serieleibniz serieleibniz.c

serieleibniz_hilos: serieleibniz_hilos.c
		gcc -o serieleibniz_hilos serieleibniz_hilos.c -pthread

serieleibniz_hilosprocesos: serieleibniz_hilosprocesos.c
		gcc -o serieleibniz_hilosprocesos serieleibniz_hilosprocesos.c

serieleibniz_procesos: serieleibniz_procesos.c
		gcc -o serieleibniz_procesos serieleibniz_procesos.c

clean:
		rm serieleibniz serieleibniz_hilos serieleibniz_hilosprocesos serieleibniz_procesos
