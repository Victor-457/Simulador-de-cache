 #!/bin/bash

echo "clear"
if ! clear
then
    exit 1
fi

echo "removendo a origin"
if ! git remote rm origin

then
    echo "Não foi possível remover."
    exit 1
fi
echo "remoção feita com sucesso"

if ! git add .
then
    echo "Não foi possível add"
    exit 1
fi
echo "add finalizada"

if ! git commit -m "ULQ"
then
    echo "Não foi possível dar commit"
    exit 1
fi
echo "commit feito com sucesso"

if ! git remote add origin https://github.com/Victor-457/Simulador-de-cache.git
then
    echo "Não foi possível adicionar a origin"
    exit 1
fi
echo "adição feita com sucesso"

if ! git push -u origin master
then
    echo "Não upo"
    exit 1
fi
echo "upo"

	

