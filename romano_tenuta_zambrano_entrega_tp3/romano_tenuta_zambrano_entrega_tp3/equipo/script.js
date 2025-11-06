// -----------------------------------------------------------
// FUNCIÓN PRINCIPAL DE LA GALERÍA (No cambia)
// -----------------------------------------------------------
function iniciarGaleria(imagenId, anteriorBtnId, siguienteBtnId, imagenes, descripcionId) {
    let indiceActual = 0;

    // 1. Obtener los elementos del DOM 
    const imagenElemento = document.getElementById(imagenId);
    const botonAnterior = document.getElementById(anteriorBtnId);
    const botonSiguiente = document.getElementById(siguienteBtnId);
    // Encuentra el nuevo elemento de descripción
    const descripcionElemento = document.getElementById(descripcionId);

    // Si no encuentra los IDs (porque estamos en el index.html, por ejemplo), se detiene
    if (!imagenElemento || !botonAnterior || !botonSiguiente || !descripcionElemento) {
        return; 
    }

    // 2. Función para actualizar la imagen Y la descripción
    function actualizarImagen() {
        // La imagen usa la propiedad 'src' del objeto
        imagenElemento.src = imagenes[indiceActual].src; 
        
        // La descripción usa la propiedad 'descripcion' del objeto
        descripcionElemento.textContent = imagenes[indiceActual].descripcion;
    }

    // 3. Funciones de navegación
    function siguienteImagen() {
        indiceActual = (indiceActual + 1) % imagenes.length;
        actualizarImagen();
    }

    function anteriorImagen() {
        indiceActual = (indiceActual - 1 + imagenes.length) % imagenes.length;
        actualizarImagen();
    }

    // 4. Asignar los eventos y cargar la primera imagen
    botonSiguiente.addEventListener('click', siguienteImagen);
    botonAnterior.addEventListener('click', anteriorImagen);
    actualizarImagen();
}

// -----------------------------------------------------------
// ARRAYS DE IMÁGENES (Debes verificar las rutas: '../imagenes/...')
// -----------------------------------------------------------

const imagenesRomano = [
    { src: '../imagenes/img romano/romano-1.jpg', descripcion: 'Imagen perteneciente al trabajo practico de novela visual, para la catedra Pirotta.' }, 
    { src: '../imagenes/img romano/romano-2.jpg', descripcion: 'Imagen perteneciente al trabajo practico de novela visual, para la catedra Pirotta.' },
    { src: '../imagenes/img romano/romano-3.jpg', descripcion: 'Imagen perteneciente al trabajo practico de novela visual, para la catedra Pirotta.' },
    { src: '../imagenes/img romano/romano-4.jpg', descripcion: 'Imagen perteneciente al trabajo practico de novela visual, para la catedra Pirotta.' },
    { src: '../imagenes/img romano/romano-5.jpg', descripcion: 'Imagen perteneciente al trabajo practico de novela visual, para la catedra Pirotta.' },
    { src: '../imagenes/img romano/romano-6.jpg', descripcion: 'ASCII ART realizado para el trabajo practico de "Aventura Conversacional" para la catedra Tirigall.' },
];

const imagenesTenuta = [
    { src: '../imagenes/img tenuta/tenuta-1.jpg', descripcion: 'Juego de mesa, Trabajo Practico para Artes Multimediales 1.' },
    { src: '../imagenes/img tenuta/tenuta-2.jpg', descripcion: 'Trabajo practico de Fotonovela.' },
    { src: '../imagenes/img tenuta/tenuta-3.jpg', descripcion: 'Aventura Conversacional, TP realizado para la catedra Tirigall.' }
];

const imagenesZambrano = [
    { src: '../imagenes/img zambrano/zambrano-1.jpg', descripcion: 'Obra: RESPIRACION SUAVE.' },
    { src: '../imagenes/img zambrano/zambrano-2.jpg', descripcion: 'Obra: PASS THE DUTCHIE.' },
    { src: '../imagenes/img zambrano/zambrano-3.jpg', descripcion: 'Obra: PHILL PORRIL.' },
    { src: '../imagenes/img zambrano/zambrano-4.jpg', descripcion: 'Obra: SATURADO.' },
];

// -----------------------------------------------------------
// EJECUCIÓN: DETECCIÓN DE LA PÁGINA
// -----------------------------------------------------------

const tituloPagina = document.title; // Lee el título de la pestaña del navegador

if (tituloPagina.includes('Romano')) {
    // Si el título contiene la palabra "Romano", inicia la galería de Romano
    iniciarGaleria('imagen-galeria-display', 'btn-anterior', 'btn-siguiente', imagenesRomano, 'descripcion-trabajo');
    
} else if (tituloPagina.includes('Tenuta')) {
    // Si el título contiene la palabra "Tenuta", inicia la galería de Tenuta
    iniciarGaleria('imagen-galeria-display', 'btn-anterior', 'btn-siguiente', imagenesTenuta, 'descripcion-trabajo');
    
} else if (tituloPagina.includes('Zambrano')) {
    // Si el título contiene la palabra "Zambrano", inicia la galería de Zambrano
    iniciarGaleria('imagen-galeria-display', 'btn-anterior', 'btn-siguiente', imagenesZambrano, 'descripcion-trabajo');
}