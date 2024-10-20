const express = require('express');
const multer = require('multer');
const { exec } = require('child_process');
const fs = require('fs');
const os = require('os');
const path = require('path');
const upload = multer({ dest: 'uploads/' });
const app = express();

app.use(express.json());

// Ruta para recibir parámetros en formato JSON para el método SAW
app.post('/saw', (req, res) => {
    console.log('Solicitud recibida:', req.body); // Mensaje de depuración

    const { numCriterios, numAlternativas, tipoCriterio, pesoCriterio, matrizValores } = req.body;

    // Crear archivo de entrada para el programa SAW
    const inputFile = path.join(__dirname, 'input_saw.txt'); // Usar __dirname para rutas seguras
    let input = `${numCriterios} ${numAlternativas}\n`;

    // Agregar tipo y peso de cada criterio
    for (let i = 0; i < numCriterios; i++) {
        input += `${tipoCriterio[i]} ${pesoCriterio[i]}\n`;
    }

    // Agregar los valores de la matriz de alternativas
    matrizValores.forEach(fila => {
        input += fila.join(' ') + '\n';
    });

    // Guardar en archivo de texto
    fs.writeFileSync(inputFile, input);
    console.log('Archivo de entrada para SAW creado:', input); // Mensaje de depuración

    // Detectar si estamos en Windows o en Unix (Linux/macOS)
    const isWindows = os.platform() === 'win32';
    const exeFile = isWindows ? 'saw.exe' : './saw';
    const command = `${exeFile} "${inputFile}"`;  // Ruta con espacios entre comillas

// Comprobar si el archivo existe antes de ejecutar
if (fs.existsSync(inputFile)) {
    console.log('El archivo de entrada existe:', inputFile);
} else {
    console.error('El archivo de entrada no se encuentra en:', inputFile);
    return res.status(500).send('El archivo de entrada no se pudo crear.');
}

// Ejecutar el programa SAW
exec(command, (error, stdout, stderr) => {
    if (error) {
        return res.status(500).send(`Error al ejecutar SAW: ${error.message}`);
    }
    if (stderr) {
        return res.status(500).send(`Error de ejecución: ${stderr}`);
    }

    // La salida ahora contiene el mensaje completo
    console.log('Respuesta:', stdout);
    // Enviar la salida directamente como respuesta
    res.send(stdout.trim()); // .trim() para eliminar espacios en blanco adicionales
});

});

// Ruta para recibir archivo CSV con la matriz de datos para SAW
app.post('/saw/upload', upload.single('file'), (req, res) => {
    if (!req.file) {
        return res.status(400).send('No se ha recibido ningún archivo.');
    }

    const filePath = path.join(__dirname, req.file.path);  // Ruta del archivo subido

    // Detectar si estamos en Windows o Unix
    const isWindows = os.platform() === 'win32';
    const exeFile = isWindows ? 'saw.exe' : './saw';
    const command = `${exeFile} ${filePath}`;

    // Ejecutar el programa SAW
    exec(command, (error, stdout, stderr) => {
        if (error) {
            return res.status(500).send(`Error al ejecutar SAW: ${error.message}`);
        }
        if (stderr) {
            return res.status(500).send(`Error de ejecución: ${stderr}`);
        }
        // Devolver la salida del programa SAW
        res.send(stdout);
    });
});

const port = 4000;
app.listen(port, () => {
    console.log(`Servidor escuchando en el puerto ${port}`);
});