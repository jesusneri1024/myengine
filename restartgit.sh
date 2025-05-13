#!/bin/bash

# Confirmación antes de ejecutar cualquier comando
read -p "Este script sobrescribirá tu rama 'main' local y eliminará archivos no rastreados. ¿Deseas continuar? (s/N): " confirm

if [[ "$confirm" =~ ^[sS]$ ]]; then
    echo "Ejecutando operaciones de Git..."

    git checkout main
    git fetch origin
    git reset --hard origin/main
    git clean -fd

    echo "Operación completada."
else
    echo "Operación cancelada por el usuario."
    exit 1
fi
