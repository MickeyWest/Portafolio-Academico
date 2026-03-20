#include <stdio.h>
#include <string.h>
#include <locale.h>

// Función para validar la entrada de un número positivo
int validarPositivo(float *valor)
{
    while (*valor <= 0)
    {
        printf("Error: El valor debe ser positivo. Ingrese nuevamente: ");
        scanf("%f", valor);
    }
    return 1;
}

// Función para validar que el monto ejecutado no sea superior al monto asignado
int validarMonto(float *monto, float valorMaximo)
{
    while (*monto > valorMaximo)
    {
        printf("Error: El monto ejecutado no puede ser mayor que el monto asignado. Ingrese nuevamente el monto ejecutado: ");
        scanf("%f", monto);
    }
    return 1;
}

void calcularMontoPorHabitante(int poblacion, float presupuestoAsignado, float *montoPorHabitante)
{
    *montoPorHabitante = presupuestoAsignado / poblacion;
}

float calcularPresupuestoProximoAno(float sobrante, float totalAsignado)
{
    if (sobrante >= 0 && sobrante < 100)
    {
        return totalAsignado * 1.125;
    }
    else if (sobrante >= 100 && sobrante < 350)
    {
        return totalAsignado * 1.07;
    }
    else
    {
        return totalAsignado * 0.95;
    }
}

// Nueva función para buscar un municipio dentro de un estado específico
void buscarMunicipioEnEstado(char nombreEstado[], char ar_nombreMunicipio[][50], int ar_poblacion[], float ar_presupuestoAsignado[], float ar_montoEjecutado[], int N_municipios)
{
    char municipioBuscar[50];
    int encontradoMunicipio = 0;

    printf("\nIngrese el nombre del municipio que desea buscar en el estado %s: ", nombreEstado);
    scanf("%s", municipioBuscar);

    for (int j = 0; j < N_municipios; j++)
    {
        if (strcmpi(ar_nombreMunicipio[j], municipioBuscar) == 0)
        {
            encontradoMunicipio = 1;
            float montoPorHabitante;
            calcularMontoPorHabitante(ar_poblacion[j], ar_presupuestoAsignado[j], &montoPorHabitante);
            printf("\nMunicipio encontrado: %s en el estado %s\n", municipioBuscar, nombreEstado);
            printf("Número de habitantes: %d\n", ar_poblacion[j]);
            printf("Presupuesto asignado: %.2f Bs.F\n", ar_presupuestoAsignado[j]);
            printf("Monto ejecutado: %.2f Bs.F\n", ar_montoEjecutado[j]);
            printf("Monto por habitante: %.2f Bs.F\n", montoPorHabitante);
            break;
        }
    }
    if (!encontradoMunicipio)
    {
        printf("Municipio %s no encontrado en el estado %s.\n", municipioBuscar, nombreEstado);
    }
}

int main()
{
    // Declaración de variables
    char nombreEstado[50];
    char nombreMunicipio[50];
    int poblacion, N_Estados;
    float presupuestoAsignado;
    float montoEjecutado;
    float totalAsignado = 0.0;
    float totalEjecutado = 0.0;
    float totalSobrante = 0.0;
    float sobrante = 0.0;
    float proc_ejec;
    float montoPorHabitante = 0.0;
    float presupuestoEjecutadoEstado = 0.0;
    float mayorMonto = 0.0;
    int posicion = 0;
    char nombreMayor[50];

    // Arreglos
    char ar_nombreEstado[50][50];
    char ar_nombreMunicipio[50][50][50];
    int ar_poblacion[50][50];
    float ar_presupuestoAsignado[50][50];
    float ar_montoEjecutado[50][50];
    int ar_cantidadMunicipios[50];

    setlocale(LC_ALL, "spanish");

    // Bucle para procesar estados
    printf("Ingrese la cantidad de estados: ");
    scanf("%i", &N_Estados);

    int estadoActual = 0;
    while (estadoActual < N_Estados)
    {
        printf("\nEstado N%i \n", estadoActual + 1);

        // Ingreso del nombre del estado
        int T, U, A;
        do
        {
            printf("Ingrese el nombre del estado: ");
            scanf("%s", nombreEstado);
            A = 0;
            for (T = 0; T < estadoActual; T++)
            {
                if (strcmpi(ar_nombreEstado[T], nombreEstado) == 0)
                {
                    A = 1;
                }
                if (A == 1)
                {
                    printf("ESTADO YA REGISTRADO\n");
                }
            }

        } while (A == 1);
        strcpy(ar_nombreEstado[estadoActual], nombreEstado);
        // Ingreso de la cantidad de N_municipios
        int N_municipios;
        do
        {
            printf("\nIngrese la cantidad de municipios a calcular: ");
            scanf("%i", &N_municipios);
        } while (N_municipios <= 0);

        ar_cantidadMunicipios[estadoActual] = N_municipios;

        // Bucle para procesar N_municipios
        for (int municipio = 0; municipio < N_municipios; municipio++)
        {
            printf("\nMunicipio N%i\n", municipio + 1);

            // Ingreso del nombre del municipio

            do
            {
                printf("Ingrese el nombre del municipio: ");
                scanf("%s", &nombreMunicipio);
                A = 0;
                for (U = 0; U < municipio; U++)
                {
                    if (strcmpi(ar_nombreMunicipio[estadoActual][U], nombreMunicipio) == 0)
                    {
                        A = 1;
                    }
                    if (A == 1)
                    {
                        printf("MUNICIPIO YA REGISTRADO\n");
                    }
                }

            } while (A == 1);
            strcpy(ar_nombreMunicipio[estadoActual][municipio], nombreMunicipio);

            // Ingreso del número de habitantes
            do
            {
                printf("Ingrese el número de habitantes: ");
                scanf("%i", &poblacion);
            } while (poblacion <= 0);
            ar_poblacion[estadoActual][municipio] = poblacion;

            // Ingreso del presupuesto asignado
            printf("Ingrese el presupuesto asignado al municipio: ");
            scanf("%f", &presupuestoAsignado);
            validarPositivo(&presupuestoAsignado);
            ar_presupuestoAsignado[estadoActual][municipio] = presupuestoAsignado;

            // Ingreso del monto ejecutado
            printf("Ingrese el monto ejecutado: ");
            scanf("%f", &montoEjecutado);
            validarMonto(&montoEjecutado, presupuestoAsignado);
            ar_montoEjecutado[estadoActual][municipio] = montoEjecutado;

            // Cálculos
            calcularMontoPorHabitante(poblacion, presupuestoAsignado, &montoPorHabitante);
            printf("A cada habitante de %s le corresponden %0.2f Bs.F\n", nombreMunicipio, montoPorHabitante);

            // Actualización de totales
            totalAsignado += presupuestoAsignado;
            totalEjecutado += montoEjecutado;

            // Cálculo del presupuesto ejecutado en el estado
            presupuestoEjecutadoEstado += montoEjecutado;
        }

        // Cálculo del sobrante y presupuesto asignado para el próximo año
        sobrante = totalAsignado - totalEjecutado;
        totalSobrante += sobrante;
        printf("\nEstado %s\n", nombreEstado);
        printf("El presupuesto total asignado es: %0.2f Bs.F\n", totalAsignado);
        printf("El monto total ejecutado es: %0.2f Bs.F\n", totalEjecutado);
        printf("El monto total sobrante es: %0.2f Bs.F\n", sobrante);

        float presupuestoProximoAno = calcularPresupuestoProximoAno(sobrante, totalAsignado);
        printf("El presupuesto asignado para el proximo ano es: %0.2f Bs.F\n", presupuestoProximoAno); 

        // Identificación del estado con mayor monto ejecutado
        if (N_Estados >= 5)
        {
            if (totalEjecutado > mayorMonto)
            {
                strcpy(nombreMayor, nombreEstado);
                mayorMonto = totalEjecutado;
                posicion = estadoActual;
                proc_ejec = (totalSobrante * 100) / totalAsignado;
            }
        }

        // Preguntar si se desea buscar un municipio específico
        char respuesta;
        printf("\nDesea buscar los datos de un municipio específico en este estado? (s/n): ");
        scanf(" %c", &respuesta);

        if (respuesta == 's' || respuesta == 'S')
        {
            buscarMunicipioEnEstado(nombreEstado, ar_nombreMunicipio[estadoActual], ar_poblacion[estadoActual], ar_presupuestoAsignado[estadoActual], ar_montoEjecutado[estadoActual], N_municipios);
        }

        // Reinicio de variables para el siguiente estado
        totalAsignado = 0.0;
        totalEjecutado = 0.0;
        totalSobrante = 0.0;
        sobrante = 0.0;
        presupuestoEjecutadoEstado = 0.0;

        // Incremento del contador de estado
        estadoActual++;
    }

    // Impresión del estado con mayor monto ejecutado
    if (N_Estados >= 5)
    {
        printf("\nEstado con mayor monto ejecutado:\n");
        printf("Estado: %s\n", nombreMayor);
        printf("Posicion: %i\n", posicion + 1);
        printf("Monto ejecutado: %0.2f Bs.F\n", mayorMonto);
        printf("Porcentaje que dejó de ejecutar %0.2f\n", proc_ejec);
    }
    else
    {
        printf("No se puede realizar el calculo del estado con mayor monto ejecutado ");
    }

    return 0;
}