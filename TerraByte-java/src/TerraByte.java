import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

interface Reportable extends Serializable {
    String generarReporteDesempeño();
    String obtenerInformacionContacto();
}

abstract class Empleado implements Reportable, Serializable {
    protected String nombre;
    protected String idEmpleado;
    protected LocalDate fechaContratacion;

    public Empleado(String nombre, String idEmpleado, LocalDate fechaContratacion) {
        this.nombre = nombre;
        this.idEmpleado = idEmpleado;
        this.fechaContratacion = fechaContratacion;
    }

    public abstract double salarioMensual();

    @Override
    public String obtenerInformacionContacto() {
        return nombre.toLowerCase().replace(" ", ".") + "." +
                idEmpleado.toLowerCase().replace(" ", "") + "@terrabyte.com";
    }

    public String getNombre() { return nombre; }
    public String getIdEmpleado() { return idEmpleado; }
    public LocalDate getFechaContratacion() { return fechaContratacion; }
}

// SUBCLASES DE EMPLEADOS
class Desarrollador extends Empleado {
    private String lenguajePrincipal;
    private int proyectosAsignados;

    public Desarrollador(String nombre, String id, LocalDate fecha,
                         String lenguaje, int proyectos) {
        super(nombre, id, fecha);
        this.lenguajePrincipal = lenguaje;
        this.proyectosAsignados = proyectos;
    }

    @Override
    public double salarioMensual() {
        double base = 1000;
        double bonusProyectos = proyectosAsignados * 200;
        double bonusLenguaje = lenguajePrincipal.equals("Java") ? 150 : 50;
        return base + bonusProyectos + bonusLenguaje;
    }

    @Override
    public String generarReporteDesempeño() {
        return String.format("Desarrollador %s - Proyectos: %d, Lenguaje: %s",
                nombre, proyectosAsignados, lenguajePrincipal);
    }

    public String getLenguajePrincipal() { return lenguajePrincipal; }
    public int getProyectosAsignados() { return proyectosAsignados; }
}

class Diseñador extends Empleado {
    private String tipoDiseño;
    private int nivelComplejidad;

    public Diseñador(String nombre, String id, LocalDate fecha,
                     String tipo, int complejidad) {
        super(nombre, id, fecha);
        this.tipoDiseño = tipo;
        this.nivelComplejidad = complejidad;
    }

    @Override
    public double salarioMensual() {
        double base = 1200;
        double bonusComplejidad = nivelComplejidad * 150;
        return base + bonusComplejidad;
    }

    @Override
    public String generarReporteDesempeño() {
        return String.format("Diseñador %s - Especialidad: %s, Complejidad: %d/5",
                nombre, tipoDiseño, nivelComplejidad);
    }

    public String getTipoDiseño() { return tipoDiseño; }
    public int getNivelComplejidad() { return nivelComplejidad; }
}

class Tester extends Empleado {
    private String tiposPruebas;
    private int bugsEncontradosMes;

    public Tester(String nombre, String id, LocalDate fecha,
                  String pruebas, int bugs) {
        super(nombre, id, fecha);
        this.tiposPruebas = pruebas;
        this.bugsEncontradosMes = bugs;
    }

    @Override
    public double salarioMensual() {
        double base = 1100;
        double bonusBugs = bugsEncontradosMes * 10;
        return base + bonusBugs;
    }

    @Override
    public String generarReporteDesempeño() {
        return String.format("Tester %s - Pruebas: %s, Bugs encontrados: %d",
                nombre, tiposPruebas, bugsEncontradosMes);
    }

    public String getTiposPruebas() { return tiposPruebas; }
    public int getBugsEncontradosMes() { return bugsEncontradosMes; }
}

// GESTIÓN
class DepartamentoRRHH implements Serializable {
    private List<Empleado> empleados = new ArrayList<>();

    public void agregarEmpleado(Empleado empleado) {
        empleados.add(empleado);
    }

    public void eliminarEmpleado(String id) {
        empleados.removeIf(emp -> emp.getIdEmpleado().equals(id));
    }

    public double calcularNominaTotal() {
        double total = 0;
        for (Empleado emp : empleados) {
            total += emp.salarioMensual();
        }
        return total;
    }

    public List<Empleado> buscarEmpleados(String criterio) {
        List<Empleado> resultados = new ArrayList<>();
        for (Empleado emp : empleados) {
            if (emp.getNombre().toLowerCase().contains(criterio.toLowerCase()) ||
                    emp.getIdEmpleado().toLowerCase().contains(criterio.toLowerCase()) ||
                    emp.getClass().getSimpleName().toLowerCase().contains(criterio.toLowerCase())) {
                resultados.add(emp);
            }
        }
        return resultados;
    }

    public List<Empleado> getTodosEmpleados() {
        return new ArrayList<>(empleados);
    }
}

class Persistencia {
    private static final String ARCHIVO = "empleados.dat";

    public static void guardarDatos(DepartamentoRRHH dept) {
        try (ObjectOutputStream oos = new ObjectOutputStream(
                new FileOutputStream(ARCHIVO))) {
            oos.writeObject(dept);
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Error guardando datos: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static DepartamentoRRHH cargarDatos() {
        File file = new File(ARCHIVO);
        if (file.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(
                    new FileInputStream(ARCHIVO))) {
                return (DepartamentoRRHH) ois.readObject();
            } catch (IOException | ClassNotFoundException e) {
                JOptionPane.showMessageDialog(null, "Error cargando datos: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
        return new DepartamentoRRHH();
    }
}

// I.G.U
public class TerraByte extends JFrame {
    private DepartamentoRRHH departamento;
    private JTabbedPane tabbedPane;
    private DefaultTableModel empleadosModel;

    public TerraByte() {
        departamento = Persistencia.cargarDatos();

        setTitle("Sistema Gestión Empleados - TerraByte");
        setSize(800, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Configurar pestañas
        tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Registrar Empleado", crearRegistroPanel());
        tabbedPane.addTab("Listar Empleados", crearListadoPanel());
        tabbedPane.addTab("Calcular Nómina", crearNominaPanel());
        tabbedPane.addTab("Buscar Empleados", crearBusquedaPanel());

        add(tabbedPane);

        // Guardar datos al cerrar
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent e) {
                Persistencia.guardarDatos(departamento);
            }
        });
    }

    private JPanel crearRegistroPanel() {
        JPanel panel = new JPanel(new GridLayout(0, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        // Campos comunes
        JTextField nombreField = new JTextField();
        JTextField idField = new JTextField();
        JTextField fechaField = new JTextField(LocalDate.now().format(DateTimeFormatter.ISO_DATE));

        // Selector de tipo
        JComboBox<String> tipoCombo = new JComboBox<>(new String[]{"Desarrollador", "Diseñador", "Tester"});
        JPanel camposEspecificos = new JPanel(new GridLayout(0, 2, 5, 5));

        // Campos dinámicos por tipo
        tipoCombo.addActionListener(e -> {
            camposEspecificos.removeAll();
            String tipo = (String) tipoCombo.getSelectedItem();

            switch (tipo) {
                case "Desarrollador":
                    camposEspecificos.add(new JLabel("Lenguaje Principal:"));
                    camposEspecificos.add(new JTextField());
                    camposEspecificos.add(new JLabel("Proyectos Asignados:"));
                    camposEspecificos.add(new JTextField());
                    break;
                case "Diseñador":
                    camposEspecificos.add(new JLabel("Tipo de Diseño:"));
                    camposEspecificos.add(new JTextField());
                    camposEspecificos.add(new JLabel("Nivel Complejidad (1-5):"));
                    camposEspecificos.add(new JTextField());
                    break;
                case "Tester":
                    camposEspecificos.add(new JLabel("Tipos de Pruebas:"));
                    camposEspecificos.add(new JTextField());
                    camposEspecificos.add(new JLabel("Bugs Encontrados:"));
                    camposEspecificos.add(new JTextField());
                    break;
            }
            camposEspecificos.revalidate();
            camposEspecificos.repaint();
        });
        tipoCombo.setSelectedIndex(0); // Inicializar

        // Botón de registro
        JButton registrarBtn = new JButton("Registrar Empleado");
        registrarBtn.addActionListener(e -> {
            try {
                String nombre = nombreField.getText();
                String id = idField.getText();
                LocalDate fecha = LocalDate.parse(fechaField.getText());

                if (nombre.isEmpty() || id.isEmpty()) {
                    throw new Exception("Nombre e ID son obligatorios");
                }

                // Verificar si el ID ya existe
                for (Empleado emp : departamento.getTodosEmpleados()) {
                    if (emp.getIdEmpleado().equals(id)) {
                        throw new Exception("ID de empleado ya existe");
                    }
                }

                switch ((String) tipoCombo.getSelectedItem()) {
                    case "Desarrollador":
                        JTextField langField = (JTextField) camposEspecificos.getComponent(1);
                        JTextField proyField = (JTextField) camposEspecificos.getComponent(3);
                        departamento.agregarEmpleado(new Desarrollador(
                                nombre, id, fecha,
                                langField.getText(),
                                Integer.parseInt(proyField.getText())
                        ));
                        break;
                    case "Diseñador":
                        JTextField tipoField = (JTextField) camposEspecificos.getComponent(1);
                        JTextField compField = (JTextField) camposEspecificos.getComponent(3);
                        departamento.agregarEmpleado(new Diseñador(
                                nombre, id, fecha,
                                tipoField.getText(),
                                Integer.parseInt(compField.getText())
                        ));
                        break;
                    case "Tester":
                        JTextField pruebasField = (JTextField) camposEspecificos.getComponent(1);
                        JTextField bugsField = (JTextField) camposEspecificos.getComponent(3);
                        departamento.agregarEmpleado(new Tester(
                                nombre, id, fecha,
                                pruebasField.getText(),
                                Integer.parseInt(bugsField.getText())
                        ));
                        break;
                }
                JOptionPane.showMessageDialog(this, "Empleado registrado con éxito!");
                limpiarCampos(nombreField, idField);

                // Actualizar la tabla de empleados si está visible
                if (empleadosModel != null) {
                    actualizarTablaEmpleados();
                }
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Error numérico: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
        });

        // Agregar componentes
        panel.add(new JLabel("Nombre:"));
        panel.add(nombreField);
        panel.add(new JLabel("ID Empleado:"));
        panel.add(idField);
        panel.add(new JLabel("Fecha Contratación (YYYY-MM-DD):"));
        panel.add(fechaField);
        panel.add(new JLabel("Tipo de Empleado:"));
        panel.add(tipoCombo);
        panel.add(new JLabel("Campos Específicos:"));
        panel.add(camposEspecificos);
        panel.add(registrarBtn);

        return panel;
    }

    private JPanel crearListadoPanel() {
        JPanel panel = new JPanel(new BorderLayout());
        String[] columnas = {"ID", "Nombre", "Tipo", "Salario", "Contacto", "Acción"};
        empleadosModel = new DefaultTableModel(columnas, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return column == 5; // Solo la columna de acción es editable
            }
        };
        JTable tabla = new JTable(empleadosModel);

        // Configurar columna de eliminación
        TableColumn columnaAccion = tabla.getColumnModel().getColumn(5);
        columnaAccion.setCellRenderer(new ButtonRenderer());
        columnaAccion.setCellEditor(new ButtonEditor(new JCheckBox()));

        // Botón para actualizar lista
        JButton actualizarBtn = new JButton("Actualizar Lista");
        actualizarBtn.addActionListener(e -> actualizarTablaEmpleados());

        panel.add(new JScrollPane(tabla), BorderLayout.CENTER);
        panel.add(actualizarBtn, BorderLayout.SOUTH);
        return panel;
    }

    private void actualizarTablaEmpleados() {
        empleadosModel.setRowCount(0);
        for (Empleado emp : departamento.getTodosEmpleados()) {
            empleadosModel.addRow(new Object[]{
                    emp.getIdEmpleado(),
                    emp.getNombre(),
                    emp.getClass().getSimpleName(),
                    String.format("$%.2f", emp.salarioMensual()),
                    emp.obtenerInformacionContacto(),
                    "Eliminar"
            });
        }
    }

    // Clase para renderizar botones en la tabla
    class ButtonRenderer extends JButton implements TableCellRenderer {
        public ButtonRenderer() {
            setOpaque(true);
        }

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value,
                                                       boolean isSelected, boolean hasFocus, int row, int column) {
            setText((value == null) ? "" : value.toString());
            return this;
        }
    }

    // Clase para clicks en botones
    class ButtonEditor extends DefaultCellEditor {
        private String label;
        private JButton button;
        private int currentRow;

        public ButtonEditor(JCheckBox checkBox) {
            super(checkBox);
            button = new JButton();
            button.setOpaque(true);
            button.addActionListener(e -> {
                fireEditingStopped();
                String id = (String) empleadosModel.getValueAt(currentRow, 0);

                int confirm = JOptionPane.showConfirmDialog(
                        TerraByte.this,
                        "¿Eliminar empleado " + id + "?",
                        "Confirmar eliminación",
                        JOptionPane.YES_NO_OPTION
                );

                if (confirm == JOptionPane.YES_OPTION) {
                    departamento.eliminarEmpleado(id);
                    actualizarTablaEmpleados();
                    JOptionPane.showMessageDialog(
                            TerraByte.this,
                            "Empleado eliminado correctamente"
                    );
                }
            });
        }

        @Override
        public Component getTableCellEditorComponent(JTable table, Object value,
                                                     boolean isSelected, int row, int column) {
            label = (value == null) ? "" : value.toString();
            button.setText(label);
            currentRow = row;
            return button;
        }

        @Override
        public Object getCellEditorValue() {
            return label;
        }
    }

    private JPanel crearNominaPanel() {
        JPanel panel = new JPanel(new BorderLayout());
        JTextArea resultadoArea = new JTextArea();
        resultadoArea.setEditable(false);

        JButton calcularBtn = new JButton("Calcular Nómina Total");
        calcularBtn.addActionListener(e -> {
            double total = departamento.calcularNominaTotal();
            resultadoArea.setText(String.format("Total nómina mensual: $%.2f\n\nDetalle por empleado:\n", total));

            for (Empleado emp : departamento.getTodosEmpleados()) {
                resultadoArea.append(String.format(
                        "- %s (%s): $%.2f\n",
                        emp.getNombre(),
                        emp.getClass().getSimpleName(),
                        emp.salarioMensual()
                ));
            }
        });

        panel.add(new JScrollPane(resultadoArea), BorderLayout.CENTER);
        panel.add(calcularBtn, BorderLayout.SOUTH);
        return panel;
    }

    private JPanel crearBusquedaPanel() {
        JPanel panel = new JPanel(new BorderLayout());
        JTextField busquedaField = new JTextField();
        JButton buscarBtn = new JButton("Buscar");
        JTextArea resultadoArea = new JTextArea();
        resultadoArea.setEditable(false);

        buscarBtn.addActionListener(e -> {
            List<Empleado> resultados = departamento.buscarEmpleados(busquedaField.getText());
            StringBuilder sb = new StringBuilder();

            if (resultados.isEmpty()) {
                sb.append("No se encontraron empleados");
            } else {
                sb.append("Resultados de búsqueda (").append(resultados.size()).append("):\n\n");
                for (Empleado emp : resultados) {
                    sb.append("ID: ").append(emp.getIdEmpleado())
                            .append("\nNombre: ").append(emp.getNombre())
                            .append("\nTipo: ").append(emp.getClass().getSimpleName())
                            .append("\nSalario: $").append(String.format("%.2f", emp.salarioMensual()))
                            .append("\nContacto: ").append(emp.obtenerInformacionContacto())
                            .append("\nReporte: ").append(emp.generarReporteDesempeño())
                            .append("\n----------------------------\n");
                }
            }

            resultadoArea.setText(sb.toString());
        });

        JPanel topPanel = new JPanel(new BorderLayout());
        topPanel.add(new JLabel("Buscar por nombre, ID o tipo:"), BorderLayout.WEST);
        topPanel.add(busquedaField, BorderLayout.CENTER);
        topPanel.add(buscarBtn, BorderLayout.EAST);

        panel.add(topPanel, BorderLayout.NORTH);
        panel.add(new JScrollPane(resultadoArea), BorderLayout.CENTER);
        return panel;
    }

    private void limpiarCampos(JTextField... campos) {
        for (JTextField campo : campos) {
            campo.setText("");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            } catch (Exception e) {
                e.printStackTrace();
            }

            TerraByte gui = new TerraByte();
            gui.setVisible(true);
        });
    }
}