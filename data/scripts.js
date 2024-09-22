document.addEventListener("DOMContentLoaded", function() {
    const logContent = document.getElementById("log-content");
    const clearLogsButton = document.getElementById("clear-logs");
    const temperatureDisplay = document.getElementById("temperature-display");
    const toggleLumen = document.getElementById("toggle-lumen");
    const nextEffectButton = document.getElementById("next-effect");
    const toggleHeater = document.getElementById("toggle-heater");
    const timerControl = document.getElementById("timer-control");
    const confirmTimerButton = document.getElementById("confirm-timer");
    const emergencyStopButton = document.getElementById("emergency-stop");
    const countdownDisplay = document.getElementById("countdown");
    let countdownInterval;

    // Função para exibir logs
    function fetchLogs() {
        fetch("/logs")
            .then(response => response.text())
            .then(data => {
                logContent.textContent = data;
                logContent.scrollTop = logContent.scrollHeight;
            })
            .catch(error => {
                logContent.textContent = "Erro ao carregar os logs: " + error.message;
                logContent.style.borderColor = "red";
            });
    }

    // Função para buscar a temperatura do sensor
    function fetchTemperature() {
        fetch("/temperature")
            .then(response => response.text())
            .then(data => {
                temperatureDisplay.textContent = data + "°C";
            })
            .catch(error => {
                temperatureDisplay.textContent = "Erro ao carregar temperatura!";
            });
    }

    // Função para lidar com o estado do Lumen
    toggleLumen.addEventListener("change", function() {
        const lumenState = toggleLumen.checked;
        fetch("/toggle-lumen", {
            method: "POST",
            body: JSON.stringify({ state: lumenState }),
            headers: { "Content-Type": "application/json" }
        });
    });

    nextEffectButton.addEventListener("click", function() {
        fetch("/next-effect", { method: "POST" });
    });

    // Função para lidar com o estado do Heater
    toggleHeater.addEventListener("change", function() {
        const heaterState = toggleHeater.checked;
        if (heaterState) {
            timerControl.style.display = "block";
        } else {
            timerControl.style.display = "none";
            clearInterval(countdownInterval);
            countdownDisplay.textContent = "00:00:00";
        }
    });

    // Função para confirmar o Timer
    confirmTimerButton.addEventListener("click", function() {
        const minutes = document.getElementById("timer").value;
        if (!minutes || isNaN(minutes) || minutes <= 0) {
            alert("Por favor, insira um valor válido para o timer.");
            return;
        }

        const targetTime = Date.now() + minutes * 60000;
        startCountdown(targetTime);

        fetch("/start-timer", {
            method: "POST",
            body: JSON.stringify({ minutes: minutes }),
            headers: { "Content-Type": "application/json" }
        });
    });

    // Função para iniciar a contagem regressiva
    function startCountdown(targetTime) {
        clearInterval(countdownInterval);
        countdownInterval = setInterval(function() {
            const now = Date.now();
            const timeRemaining = targetTime - now;

            if (timeRemaining <= 0) {
                clearInterval(countdownInterval);
                countdownDisplay.textContent = "00:00:00";
                toggleHeater.checked = false;
                timerControl.style.display = "none";
                fetch("/stop-heater", { method: "POST" });
            } else {
                const hours = Math.floor((timeRemaining / (1000 * 60 * 60)) % 24);
                const minutes = Math.floor((timeRemaining / (1000 * 60)) % 60);
                const seconds = Math.floor((timeRemaining / 1000) % 60);
                countdownDisplay.textContent = `${hours.toString().padStart(2, '0')}:${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
            }
        }, 1000);
    }

    // Parada de emergência
    emergencyStopButton.addEventListener("click", function() {
        clearInterval(countdownInterval);
        countdownDisplay.textContent = "00:00:00";
        toggleHeater.checked = false;
        timerControl.style.display = "none";
        fetch("/stop-heater", { method: "POST" });
    });

    // Atualiza os logs e a temperatura a cada 10 segundos
    setInterval(fetchLogs, 10000);
    setInterval(fetchTemperature, 5000);
});
