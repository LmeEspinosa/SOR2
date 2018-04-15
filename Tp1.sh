#!/bin/bash
Bandera=false
Menu='Seleccione:'
opcion=("Info MBR" "Leer BootSector" "Leer FileSystem" "Ver MBR en Bless" "Salir")
select op in "${opcion[@]}"
do
if ! $Bandera; then
   echo "Comencemos" 
   sudo mount test.img /mnt -o loop,umask=000   
   Bandera=true
fi
    case $op in
        "Info MBR")
            echo "Seleccionaste Info MBR"
                  gcc read_mbr.c -o mbr
                 # gnome-terminal gnome-terminal -x sh -c 'touch tp1Log.txt; tail -f tp1Log.txt; exec bash'
                  ./mbr >>Tp1Log.txt; cat Tp1Log.txt | less
            ;;
        "Leer BootSector")
            echo "Seleccionaste Leer BootSector"
                 gcc read_boot.c -o boot
                 ./boot>>Tp1Log.txt; cat Tp1Log.txt
            ;;
        "Leer FileSystem")
            echo "Seleccionaste Leer FileSystem"
                 gcc read_root.c -o root
                 ./root>>Tp1Log.txt; cat Tp1Log.txt
            ;;
        "Ver MBR en Bless")
           echo "Ejecutando Bless"
                bless test.img&
            ;;
        "Salir")
            if [ $Bandera ] ; then 
               sudo umount /mnt
            fi
            break
            ;;
        *) echo Opcion Invalida;;
    esac
done

