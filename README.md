Simulation
==========
Copy semaphore.h and semaphore.cpp and street.h and street.cpp in the C:\PowerDEVS\atomics\sources

Same with car_generator.cpp and car_generator.h and corner.h and corner.cpp

Note:
- If on the corner, the cars have less speed on That street, 
  then ignore the corner many cars.

  For that the system no collapse, or the street that runs from two corner to one corner decender its 
  speed or the one corner increase its speed.

en el cambio de semaforos pasan 3 segundos que permite que avance el ultimo auto en entrar a la esquina.
Si la velocidad de la esquina es tal que los autos en tres segundos avanza menos que la longitud del mismo
el primer auto de la calle con el verde se ignorara.

como la calle 3 va mas rapido que la dos, y la esquina mas aun, cuando entre un auto a la calle dos tardara mas en avanzar 
dos metros que en la esquina -> dos opciones, disminuir la vel en calle 3 o aumentar en calle 2



