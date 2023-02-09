# ¿Por qué ponemos todos los registros?
Porque puede que la BIOS los setee adecuadamente o puede que no, no lo
sabemos. Puede que no les ponga los valores correctos (necesitamos la
dirección de carga 0x7c00 para que todo funcione).  
Por eso es buena práctica ponerlos nosotros y no asumir que la BIOS hace
cualquier cosa. La BIOS puede también asumir algo que nosotros no sabemos.

# Interrupciones
Cuando se ponen las interrupciones, se pone el manejador *handle_int_zero*
en los dos primeros bytes de memoria (índice 0 de la tabla de interrupts).
Para hacer eso se pone la instrucción `mov word [ss:0x00], handle`. Si no
se pusiera el `ss` se usaría el segmento de datos (que por el `mov` de
más arriba contiene 0x7c0). Usamos `ss` porque arriba lo hemos puesto
apuntando a 0x00.
