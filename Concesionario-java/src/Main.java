import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

interface Vendible {
    void aplicarDescuento(double porcentaje);
}

abstract class Vehiculo implements Vendible, Serializable {
    protected String marca;
    protected String modelo;
    protected int añoFabricacion;
    protected double precioBase;

    public Vehiculo(String marca, String modelo, int añoFabricacion, double precioBase) {
        this.marca = marca;
        this.modelo = modelo;
        this.añoFabricacion = añoFabricacion;
        this.precioBase = precioBase;
    }

    public abstract double calcularPrecioFinalVenta();
}

// COCHE
class Coche extends Vehiculo {
    private int numeroPuertas;
    private String tipoCombustible;

    public Coche(String marca, String modelo, int año, double precio, int puertas, String combustible) {
        super(marca, modelo, año, precio);
        this.numeroPuertas = puertas;
        this.tipoCombustible = combustible;
    }

    @Override
    public double calcularPrecioFinalVenta() {
        double impuesto = tipoCombustible.equalsIgnoreCase("eléctrico") ? 0.05 : 0.18;
        return precioBase * (1 + impuesto);
    }

    @Override
    public void aplicarDescuento(double porcentaje) {
        precioBase = precioBase * (1 - porcentaje/100.0);
    }
}

// MOTO
class Moto extends Vehiculo {
    private int cilindrada;
    private String tipoMoto;

    public Moto(String marca, String modelo, int año, double precio, int cilindrada, String tipo) {
        super(marca, modelo, año, precio);
        this.cilindrada = cilindrada;
        this.tipoMoto = tipo;
    }

    @Override
    public double calcularPrecioFinalVenta() {
        double recargo = tipoMoto.equalsIgnoreCase("deportiva") ? 0.15 : 0.10;
        return precioBase * (1 + recargo);
    }

    @Override
    public void aplicarDescuento(double porcentaje) {
        precioBase = precioBase * (1 - porcentaje/100.0);
    }
}


// CAMIONETA
class Camioneta extends Vehiculo {
    private double capacidadCargaKg;
    private String traccion;

    public Camioneta(String marca, String modelo, int año, double precio, double carga, String traccion) {
        super(marca, modelo, año, precio);
        this.capacidadCargaKg = carga;
        this.traccion = traccion;
    }

    @Override
    public double calcularPrecioFinalVenta() {
        double impuesto = traccion.equalsIgnoreCase("4x4") ? 0.12 : 0.08;
        return precioBase * (1 + impuesto);
    }

    @Override
    public void aplicarDescuento(double porcentaje) {
        precioBase = precioBase * (1 - porcentaje / 100.0);
    }
}

// CLIENTE
class Cliente implements Serializable {
    private String nombre;
    private double presupuesto;

    public Cliente(String nombre, String id, double presupuesto) {
        this.nombre = nombre;
        this.presupuesto = presupuesto;
    }

    public String getNombre() { return nombre; }
    public double getPresupuesto() { return presupuesto; }
}

// CONCESIONARIO
class Concesionario {
    private ArrayList<Vehiculo> inventario;
    private static final String ARCHIVO = "inventario.dat";

    public Concesionario() {
        inventario = new ArrayList<>();
        cargarInventario();
    }

    public void guardarInventario() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(ARCHIVO))) {
            oos.writeObject(inventario);
        } catch (IOException e) {
            System.err.println("Error guardando inventario: " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    private void cargarInventario() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(ARCHIVO))) {
            inventario = (ArrayList<Vehiculo>) ois.readObject();
        } catch (FileNotFoundException e) {
            System.out.println("Inventario nuevo. Creando archivo...");
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Error cargando inventario: " + e.getMessage());
        }
    }

    public void registrarVehiculo(Vehiculo v) {
        inventario.add(v);
        guardarInventario();
    }

    public String consultarInventario() {
        StringBuilder sb = new StringBuilder();
        for (Vehiculo v : inventario) {
            String tipo = v instanceof Coche ? "Coche" :
                    v instanceof Moto ? "Moto" : "Camioneta";
            sb.append("[").append(tipo).append("] ")
                    .append(v.marca).append(" ").append(v.modelo)
                    .append(" - Precio Final: ").append(String.format("%,.2f", v.calcularPrecioFinalVenta())).append("\n");
        }
        return sb.toString();
    }

    public List<Vehiculo> buscarVehiculo(String criterio) {
        List<Vehiculo> resultados = new ArrayList<>();
        for (Vehiculo v : inventario) {
            if (v.marca.equalsIgnoreCase(criterio) ||
                    v.modelo.equalsIgnoreCase(criterio)) {
                resultados.add(v);
            }
        }
        return resultados;
    }

    public void realizarVenta(Cliente cliente, Vehiculo vehiculo, double descuento) {
        vehiculo.aplicarDescuento(descuento);
        inventario.remove(vehiculo);
        guardarInventario();
    }
}

// I.G.U
public class Main extends JFrame {
    private Concesionario concesionario;
    private JTextArea outputArea;

    public Main() {
        concesionario = new Concesionario();
        setTitle("Andes Car - Gestión de Inventario");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Área de texto para salida
        outputArea = new JTextArea();
        outputArea.setEditable(false);
        add(new JScrollPane(outputArea), BorderLayout.CENTER);

        // Panel de botones
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());

        JButton btnRegistrar = new JButton("Registrar Vehículo");
        btnRegistrar.addActionListener(this::registrarVehiculo);

        JButton btnConsultar = new JButton("Consultar Inventario");
        btnConsultar.addActionListener(e -> outputArea.setText(concesionario.consultarInventario()));

        JButton btnBuscar = new JButton("Buscar Vehículo");
        btnBuscar.addActionListener(this::buscarVehiculo);

        JButton btnVender = new JButton("Realizar Venta");
        btnVender.addActionListener(this::realizarVenta);

        buttonPanel.add(btnRegistrar);
        buttonPanel.add(btnConsultar);
        buttonPanel.add(btnBuscar);
        buttonPanel.add(btnVender);
        add(buttonPanel, BorderLayout.NORTH);

        setVisible(true);
    }

    private void registrarVehiculo(ActionEvent e) {
        JDialog dialog = new JDialog(this, "Registrar Vehículo", true);
        dialog.setLayout(new BorderLayout());

        // Panel principal con pestañas
        JTabbedPane tabbedPane = new JTabbedPane();

        // Crear paneles independientes para cada tipo
        JPanel carroPanel = crearVehiculoPanel();
        JPanel motoPanel = crearVehiculoPanel();
        JPanel camionetaPanel = crearVehiculoPanel();

        // Añadir componentes específicos
        anadirComponentesCarro(carroPanel);
        anadirComponentesMoto(motoPanel);
        anadirComponentesCamioneta(camionetaPanel);

        // Añadir pestañas
        tabbedPane.addTab("Coche", carroPanel);
        tabbedPane.addTab("Moto", motoPanel);
        tabbedPane.addTab("Camioneta", camionetaPanel);

        // Botón Guardar
        JButton btnGuardar = new JButton("Guardar");
        btnGuardar.addActionListener(ev -> procesoRegistro(dialog, tabbedPane));

        dialog.add(tabbedPane, BorderLayout.CENTER);
        dialog.add(btnGuardar, BorderLayout.SOUTH);
        dialog.pack();
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    // Crear panel base con campos comunes
    private JPanel crearVehiculoPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2, 10, 10)); // 6 filas para campos comunes + específicos

        // Campos comunes
        panel.add(new JLabel("Marca:"));
        JTextField marcaField = new JTextField();
        panel.add(marcaField);

        panel.add(new JLabel("Modelo:"));
        JTextField modeloField = new JTextField();
        panel.add(modeloField);

        panel.add(new JLabel("Año Fabricación:"));
        JTextField añoField = new JTextField();
        panel.add(añoField);

        panel.add(new JLabel("Precio Base:"));
        JTextField precioField = new JTextField();
        panel.add(precioField);

        // Almacenar referencias
        panel.putClientProperty("marcaField", marcaField);
        panel.putClientProperty("modeloField", modeloField);
        panel.putClientProperty("añoField", añoField);
        panel.putClientProperty("precioField", precioField);

        return panel;
    }

    // Añadir componentes específicos para coches
    private void anadirComponentesCarro(JPanel panel) {
        panel.add(new JLabel("N° Puertas:"));
        JTextField puertasField = new JTextField();
        panel.add(puertasField);

        panel.add(new JLabel("Combustible:"));
        JComboBox<String> combustibleCombo = new JComboBox<>(new String[]{"Gasolina", "Diésel", "Eléctrico"});
        panel.add(combustibleCombo);

        panel.putClientProperty("puertasField", puertasField);
        panel.putClientProperty("combustibleCombo", combustibleCombo);
    }

    // Añadir componentes específicos para motos
    private void anadirComponentesMoto(JPanel panel) {
        panel.add(new JLabel("Cilindrada (cc):"));
        JTextField cilindradaField = new JTextField();
        panel.add(cilindradaField);

        panel.add(new JLabel("Tipo Moto:"));
        JComboBox<String> tipoMotoCombo = new JComboBox<>(new String[]{"Deportiva", "Touring", "Scooter"});
        panel.add(tipoMotoCombo);

        panel.putClientProperty("cilindradaField", cilindradaField);
        panel.putClientProperty("tipoMotoCombo", tipoMotoCombo);
    }

    // Añadir componentes específicos para camionetas
    private void anadirComponentesCamioneta(JPanel panel) {
        panel.add(new JLabel("Capacidad (kg):"));
        JTextField capacidadField = new JTextField();
        panel.add(capacidadField);

        panel.add(new JLabel("Tracción:"));
        JComboBox<String> traccionCombo = new JComboBox<>(new String[]{"4x2", "4x4"});
        panel.add(traccionCombo);

        panel.putClientProperty("capacidadField", capacidadField);
        panel.putClientProperty("traccionCombo", traccionCombo);
    }

    // Procesar el registro del vehículo
    private void procesoRegistro(JDialog dialog, JTabbedPane tabbedPane) {
        try {
            int tabIndex = tabbedPane.getSelectedIndex();
            JPanel currentPanel = (JPanel) tabbedPane.getComponentAt(tabIndex);

            // Obtener campos comunes
            JTextField marcaField = (JTextField) currentPanel.getClientProperty("marcaField");
            JTextField modeloField = (JTextField) currentPanel.getClientProperty("modeloField");
            JTextField añoField = (JTextField) currentPanel.getClientProperty("añoField");
            JTextField precioField = (JTextField) currentPanel.getClientProperty("precioField");

            // Validar campos comunes
            String marca = marcaField.getText().trim();
            String modelo = modeloField.getText().trim();
            if(marca.isEmpty() || modelo.isEmpty()) {
                JOptionPane.showMessageDialog(dialog, "Marca y modelo son obligatorios", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            int año = 0;
            double precio = 0;

            try {
                año = Integer.parseInt(añoField.getText().trim());
                precio = Double.parseDouble(precioField.getText().trim());
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(dialog, "Año y precio deben ser números válidos", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            // Crear vehículo según el tipo
            Vehiculo vehiculo = null;
            switch(tabIndex) {
                case 0: // Coche
                    JTextField puertasField = (JTextField) currentPanel.getClientProperty("puertasField");
                    JComboBox<String> combustibleCombo = (JComboBox<String>) currentPanel.getClientProperty("combustibleCombo");

                    try {
                        int puertas = Integer.parseInt(puertasField.getText().trim());
                        String combustible = (String) combustibleCombo.getSelectedItem();
                        vehiculo = new Coche(marca, modelo, año, precio, puertas, combustible);
                    } catch (NumberFormatException ex) {
                        JOptionPane.showMessageDialog(dialog, "Número de puertas debe ser un valor numérico", "Error", JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                    break;

                case 1: // Moto
                    JTextField cilindradaField = (JTextField) currentPanel.getClientProperty("cilindradaField");
                    JComboBox<String> tipoMotoCombo = (JComboBox<String>) currentPanel.getClientProperty("tipoMotoCombo");

                    try {
                        int cilindrada = Integer.parseInt(cilindradaField.getText().trim());
                        String tipoMoto = (String) tipoMotoCombo.getSelectedItem();
                        vehiculo = new Moto(marca, modelo, año, precio, cilindrada, tipoMoto);
                    } catch (NumberFormatException ex) {
                        JOptionPane.showMessageDialog(dialog, "Cilindrada debe ser un valor numérico", "Error", JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                    break;

                case 2: // Camioneta
                    JTextField capacidadField = (JTextField) currentPanel.getClientProperty("capacidadField");
                    JComboBox<String> traccionCombo = (JComboBox<String>) currentPanel.getClientProperty("traccionCombo");

                    try {
                        double capacidad = Double.parseDouble(capacidadField.getText().trim());
                        String traccion = (String) traccionCombo.getSelectedItem();
                        vehiculo = new Camioneta(marca, modelo, año, precio, capacidad, traccion);
                    } catch (NumberFormatException ex) {
                        JOptionPane.showMessageDialog(dialog, "Capacidad debe ser un valor numérico", "Error", JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                    break;
            }

            concesionario.registrarVehiculo(vehiculo);
            outputArea.append("Vehículo registrado: " +
                    tabbedPane.getTitleAt(tabIndex) + " " + marca + " " + modelo + "\n");
            dialog.dispose();

        } catch (Exception ex) {
            JOptionPane.showMessageDialog(dialog,
                    "Error inesperado: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void buscarVehiculo(ActionEvent e) {
        String criterio = JOptionPane.showInputDialog(this, "Ingrese marca o modelo:");
        if (criterio != null && !criterio.trim().isEmpty()) {
            List<Vehiculo> resultados = concesionario.buscarVehiculo(criterio.trim());
            if (resultados.isEmpty()) {
                outputArea.setText("No se encontraron vehículos para: " + criterio);
            } else {
                StringBuilder sb = new StringBuilder();
                for (Vehiculo v : resultados) {
                    String tipo = v instanceof Coche ? "Coche" :
                            v instanceof Moto ? "Moto" : "Camioneta";
                    sb.append("[").append(tipo).append("] ")
                            .append(v.marca).append(" ").append(v.modelo)
                            .append(" - Precio: ").append(String.format("%,.2f", v.calcularPrecioFinalVenta()))
                            .append("\n");
                }
                outputArea.setText(sb.toString());
            }
        }
    }

    private void realizarVenta(ActionEvent e) {
        JDialog dialog = new JDialog(this, "Vender Vehículo", true);
        dialog.setLayout(new GridLayout(0, 2, 10, 10));

        JTextField clienteField = new JTextField(15);
        dialog.add(new JLabel("Nombre Cliente:"));
        dialog.add(clienteField);

        JTextField vehiculoField = new JTextField(15);
        dialog.add(new JLabel("Marca Vehículo:"));
        dialog.add(vehiculoField);

        JTextField descuentoField = new JTextField(15);
        dialog.add(new JLabel("Descuento (%):"));
        dialog.add(descuentoField);

        JButton btnVender = new JButton("Confirmar Venta");
        btnVender.addActionListener(ev -> {
            try {
                String nombreCliente = clienteField.getText().trim();
                String marcaVehiculo = vehiculoField.getText().trim();
                double descuento = Double.parseDouble(descuentoField.getText().trim());

                if (nombreCliente.isEmpty() || marcaVehiculo.isEmpty()) {
                    JOptionPane.showMessageDialog(dialog, "Todos los campos son obligatorios", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Buscar vehículo
                List<Vehiculo> resultados = concesionario.buscarVehiculo(marcaVehiculo);
                if(!resultados.isEmpty()) {
                    Vehiculo v = resultados.get(0);
                    Cliente cliente = new Cliente(nombreCliente, "ID-TEMP", 1000000);

                    concesionario.realizarVenta(cliente, v, descuento);
                    outputArea.append("Venta realizada: " + v.marca + " " + v.modelo +
                            " a " + nombreCliente + " con " + descuento + "% descuento\n");
                    dialog.dispose();
                } else {
                    JOptionPane.showMessageDialog(dialog, "Vehículo no encontrado", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(dialog, "Descuento debe ser un número válido", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });

        dialog.add(new JLabel());
        dialog.add(btnVender);
        dialog.pack();
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Main());
    }
}