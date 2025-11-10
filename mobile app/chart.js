// Konfigurasi Firebase
const firebaseConfig = {
    databaseURL: "https://greenhouse-57ba1-default-rtdb.asia-southeast1.firebasedatabase.app"
};

// Inisialisasi Firebase
firebase.initializeApp(firebaseConfig);
const database = firebase.database();

// Nilai awal
let suhu = 31;
let kelembapan = 80.2;

// Fungsi update tampilan
function updateDisplay(suhu, kelembapan) {
    // Update nilai di atas bar
    document.getElementById('val-suhu').innerText = suhu;
    document.getElementById('val-rh').innerText = kelembapan;

    // Update bar graph
    document.getElementById('bar-suhu').style.height = (suhu / 40 * 100) + '%';
    document.getElementById('barval-suhu').innerText = suhu + '°C';

    document.getElementById('bar-rh').style.height = kelembapan + '%';
    document.getElementById('barval-rh').innerText = kelembapan + '%';
}

// Update tampilan awal
updateDisplay(suhu, kelembapan);

// Baca data dari Firebase
const tempRef = database.ref('Sensor/Temeperature');
tempRef.on('value', (snapshot) => {
    if (snapshot.exists()) {
        suhu = parseFloat(snapshot.val()).toFixed(1);
        updateDisplay(suhu, kelembapan);
    }
});

const humiRef = database.ref('Sensor/Humidity');
humiRef.on('value', (snapshot) => {
    if (snapshot.exists()) {
        kelembapan = parseFloat(snapshot.val()).toFixed(1);
        updateDisplay(suhu, kelembapan);
    }
});