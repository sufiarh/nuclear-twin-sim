import pandas as pd
import matplotlib.pyplot as plt

try:
    # Membaca data hasil simulasi C++
    data = pd.read_csv('build/reactor_transient_data.csv') # Sesuaikan letak path file CSV-mu

    fig, ax1 = plt.subplots(figsize=(10, 5))

    # Plot Daya Reaktor (Sumbu Y Kiri)
    color = 'tab:red'
    ax1.set_xlabel('Waktu (detik)', fontsize=12)
    ax1.set_ylabel('Daya Reaktor (%)', color=color, fontsize=12)
    ax1.plot(data['Time'], data['PowerPercent'], color=color, linewidth=2, label='Daya (%)')
    ax1.tick_params(axis='y', labelcolor=color)
    ax1.grid(True, linestyle='--')

    # Plot Suhu Bahan Bakar (Sumbu Y Kanan)
    ax2 = ax1.twinx()
    color = 'tab:blue'
    ax2.set_ylabel('Temperatur Bahan Bakar (°C)', color=color, fontsize=12)
    ax2.plot(data['Time'], data['FuelTemp'], color=color, linewidth=2, linestyle='--', label='Suhu (°C)')
    ax2.tick_params(axis='y', labelcolor=color)

    plt.title('Grafik Analisis Transien Reaktor Nuklir (Mekanisme SCRAM/Umpan Balik)', fontsize=14, fontweight='bold')
    fig.tight_layout()

    # Simpan grafik sebagai gambar untuk dokumentasi GitHub
    plt.savefig('reactor_transient_plot.png', dpi=300)
    print("Grafik 'reactor_transient_plot.png' berhasil dibuat!")

except FileNotFoundError:
    print("File CSV tidak ditemukan. Jalankan simulator C++ dan aktifkan fitur log (tombol 'l') terlebih dahulu.")
