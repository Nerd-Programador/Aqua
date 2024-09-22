document.addEventListener("DOMContentLoaded", function () {
    const form = document.querySelector("form");
    const fileInput = document.querySelector("input[type='file']");

    form.addEventListener("submit", function (event) {
        if (fileInput.files.length === 0) {
            alert("Por favor, selecione um arquivo para upload.");
            event.preventDefault();
        }
    });
});
