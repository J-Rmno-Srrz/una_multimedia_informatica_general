
/* ----------------------------- Helpers básicos ----------------------------- */
// Atajo semántico para no repetir document.getElementById
const $id = (id) => document.getElementById(id);

// Debounce: función de orden superior que “aplaza” la ejecución de fn
const debounce = (fn, ms = 180) => {
  let t; return (...args) => { clearTimeout(t); t = setTimeout(() => fn(...args), ms); };
};

/* ------------------------ COMPOSE (fábrica de reglas) ----------------------- */
/*
  compose(...validators) crea UN validador que corre varios chequeos en orden.
  Cada validador individual devuelve: null (OK) o "mensaje de error" (string).
  Si alguno falla, se corta y devuelve su mensaje; si ninguno falla, retorna null.
*/
const compose = (...validators) => (value) =>
  validators.reduce((error, v) => error || v(value), null);

/* -------------------- Mensajes + validadores atómicos ---------------------- */
const MSG = {
  required: 'Este campo es obligatorio.',
  min:      (n)    => `Mínimo ${n} caracteres.`,
  max:      (n)    => `Máximo ${n} caracteres.`,
  between:  (a, b) => `Entre ${a} y ${b} caracteres.`,
  email:    'Por favor, ingrese un correo electrónico válido.',
};

// Todos devuelven: null (OK) o string (error)
const v_required = (msg = MSG.required) => (v) =>
  String(v).trim().length ? null : (typeof msg === 'function' ? msg() : msg);

const v_min = (n, msg = MSG.min(n)) => (v) =>
  String(v).trim().length >= n ? null : (typeof msg === 'function' ? msg(n) : msg);

const v_max = (n, msg = MSG.max(n)) => (v) =>
  String(v).trim().length <= n ? null : (typeof msg === 'function' ? msg(n) : msg);

const v_between = (a, b, msg = MSG.between(a, b)) => (v) => {
  const len = String(v).trim().length;
  return (len >= a && len <= b) ? null : (typeof msg === 'function' ? msg(a, b) : msg);
};

const v_email = (msg = MSG.email) => (v) =>
  /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(String(v).trim()) ? null : msg;

/* --------------------------- Setup al cargar la página ---------------------- */
document.addEventListener('DOMContentLoaded', () => {
  const form    = $id('contactForm');
  if (!form) return; // si no está en esta página, salimos

  const name    = $id('name');
  const email   = $id('email');
  const message = $id('message');

  const nameError    = $id('nameError');
  const emailError   = $id('emailError');
  const messageError = $id('messageError');
  const messageCount = $id('messageCount');
  const formMessage  = $id('formMessage');

  // Validadores compuestos por campo (usando compose)
  const validators = {
    name:    compose(v_required(), v_min(2)),
    email:   compose(v_required(), v_email()),
    message: compose(v_required(), v_between(10, message?.maxLength || 500))
  };

  // Pinta clases y ARIA, y escribe el mensaje de error en el contenedor asociado
  const setFieldState = (input, errorMsg, errorBox) => {
    if (errorMsg) {
      input.classList.add('error');
      input.classList.remove('valid');
      input.setAttribute('aria-invalid', 'true');
      if (errorBox) errorBox.textContent = errorMsg;
    } else {
      input.classList.remove('error');
      input.classList.add('valid');
      input.removeAttribute('aria-invalid');
      if (errorBox) errorBox.textContent = '';
    }
  };

  // Valida un campo por clave (name/email/message) y devuelve el error o null
  const validateField = (key) => {
    const input = key === 'name' ? name : key === 'email' ? email : message;
    const errorBox = key === 'name' ? nameError : key === 'email' ? emailError : messageError;
    const validator = validators[key];
    if (!input || !validator) return null;
    const error = validator(input.value);
    setFieldState(input, error, errorBox);
    return error;
  };

  // Valida todos y devuelve un objeto con los errores actuales
  const validateAll = () => {
    return {
      name:    validateField('name'),
      email:   validateField('email'),
      message: validateField('message'),
    };
  };

  // Contador de caracteres del textarea
  if (message && messageCount) {
    const max = message.maxLength || 500;
    const updateCount = () => { messageCount.textContent = `${message.value.length} / ${max}`; };
    message.addEventListener('input', updateCount);
    updateCount();
  }

  // Validación en vivo: input (debounce) + blur (inmediata)
  if (name) {
    name.addEventListener('input', debounce(() => { validateField('name'); formMessage.textContent = ''; }, 150));
    name.addEventListener('blur', () => validateField('name'));
  }
  if (email) {
    email.addEventListener('input', debounce(() => { validateField('email'); formMessage.textContent = ''; }, 150));
    email.addEventListener('blur', () => validateField('email'));
  }
  if (message) {
    message.addEventListener('input', debounce(() => { validateField('message'); formMessage.textContent = ''; }, 150));
    message.addEventListener('blur', () => validateField('message'));
  }
});

/* ----------------------------- Envío (onsubmit) ----------------------------- */
/*
  Esta función es llamada por el atributo onsubmit del form:
  <form id="contactForm" onsubmit="validateForm(event)" ...>
*/
function validateForm(event) {
  event.preventDefault(); // que no se envíe sin pasar nuestra validación

  const name         = $id('name');
  const email        = $id('email');
  const message      = $id('message');
  const nameError    = $id('nameError');
  const emailError   = $id('emailError');
  const messageError = $id('messageError');
  const formMessage  = $id('formMessage');

  // Re-definimos (por si cargaron este archivo antes del DOMContentLoaded)
  const validators = {
    name:    compose(v_required(), v_min(2)),
    email:   compose(v_required(), v_email()),
    message: compose(v_required(), v_between(10, message?.maxLength || 500))
  };

  // Helpers locales
  const setFieldState = (input, errorMsg, errorBox) => {
    if (errorMsg) {
      input.classList.add('error'); input.classList.remove('valid');
      input.setAttribute('aria-invalid', 'true');
      if (errorBox) errorBox.textContent = errorMsg;
    } else {
      input.classList.remove('error'); input.classList.add('valid');
      input.removeAttribute('aria-invalid');
      if (errorBox) errorBox.textContent = '';
    }
  };

  // Validación final (por si tocan “Enviar” sin interactuar)
  const errName    = validators.name(name.value);
  const errEmail   = validators.email(email.value);
  const errMessage = validators.message(message.value);

  setFieldState(name,    errName,    nameError);
  setFieldState(email,   errEmail,   emailError);
  setFieldState(message, errMessage, messageError);

  const hasErrors = !!(errName || errEmail || errMessage);

  if (hasErrors) {
    formMessage.textContent = 'Revisá los campos en rojo.';
    formMessage.classList.remove('success');
    formMessage.classList.add('error');
    return; // no seguimos con el envío
  }

  // Si está todo OK: construimos y disparamos el mailto (como en tu versión)
  const subject = encodeURIComponent(`Nuevo mensaje de contacto de ${name.value.trim()}`);
  const body    = encodeURIComponent(
    `Nombre: ${name.value.trim()}\nCorreo: ${email.value.trim()}\nMensaje:\n${message.value.trim()}`
  );
  const mailtoLink = `mailto:tu-email@gmail.com?subject=${subject}&body=${body}`;

  window.location.href = mailtoLink;

  formMessage.textContent = 'Formulario enviado correctamente.';
  formMessage.classList.remove('error');
  formMessage.classList.add('success');

  // Si querés limpiar el formulario después:
  // $id('contactForm').reset();
  // (y actualizar contador)
  // const messageCount = $id('messageCount');
  // if (messageCount) messageCount.textContent = '0 / 500';
}

/* ---------------------------------------------------- */
/* ==============       GALERIA      ================== */
/* ---------------------------------------------------- */

// Selecciona todos los elementos con la clase 'gallery-item' y agrega un evento 'click' a cada uno
document.querySelectorAll('.gallery-item').forEach(item => {
    item.addEventListener('click', () => {
        // Obtiene la URL de la imagen desde el elemento <img> dentro de 'gallery-item'
        const imageSrc = item.querySelector('img').src;

        // Llama a la función openModal() pasando la URL de la imagen seleccionada
        openModal(imageSrc);
    });
});

// Función para abrir un modal con la imagen seleccionada
function openModal(imageSrc) {
    // Crea un nuevo elemento <div> para el modal
    const modal = document.createElement('div');
    modal.classList.add('modal');  // Asigna la clase 'modal' al div para darle estilo
    
    // Define el contenido HTML del modal (que era un div), incluyendo un botón de cierre y la imagen
    modal.innerHTML = `
        <div class="modal-content">
            <span class="close">&times;</span>  <!-- Icono de cierre (×) -->
            <img src="${imageSrc}" alt="Imagen de proyecto" />  <!-- Imagen seleccionada con la URL proporcionada -->
        </div>
    `;
    
    // Agrega el modal al documento, colocándolo como un elemento hijo de <body>
    document.body.appendChild(modal);

    // Agrega un evento para cerrar el modal al hacer clic en el icono de cierre
    modal.querySelector('.close').onclick = () => modal.remove();

    // Agrega un evento para cerrar el modal al hacer clic en cualquier área fuera del contenido modal
    modal.onclick = () => modal.remove();
}