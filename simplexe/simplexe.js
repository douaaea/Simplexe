// simplex.js

// Function to optimize using Simplex algorithm
function optimize() {
    // Clear previous tables
    const tableContainer = document.getElementById("iteration_tables");
    tableContainer.innerHTML = "";

    // Retrieve objective function coefficients
    const numVariables = parseInt(document.getElementById("num_variables").value);
    const objectiveCoefficients = {};
    for (let i = 1; i <= numVariables; i++) {
        const coefficient = parseInt(document.getElementById(`coef_x${i}`).value);
        objectiveCoefficients[`x${i}`] = coefficient;
    }

    // Retrieve constraint coefficients
    const constraints = [];
    const constraintInputsDiv = document.getElementById("constraint_inputs");
    const inputs = constraintInputsDiv.getElementsByTagName("input");

    for (let i = 0; i < inputs.length; i += (numVariables + 1)) {
        const constraint = { Z: 0 };
        for (let j = 0; j < numVariables; j++) {
            constraint[`x${j + 1}`] = parseInt(inputs[i + j].value);
        }
        constraint["constant"] = parseInt(inputs[i + numVariables].value);
        constraints.push(constraint);
    }

    // Add slack variables
    constraints.forEach((constraint, index) => {
        constraint[`e${index + 1}`] = 1;
    });

    // Create initial tableau
    const tableau = [objectiveCoefficients, ...constraints];

    // Display the tableau
    displayTableau(tableau);

    // Simplex algorithm
    let pivotColumn = selectPivotColumn(tableau);
    while (pivotColumn) {
        const pivotRow = selectPivotRow(tableau, pivotColumn);
        if (pivotRow === null) {
            return; // No feasible solution
        }
        gaussianElimination(tableau, pivotRow, pivotColumn);
        pivotColumn = selectPivotColumn(tableau);
    }

    // Display final tableau
    displayTableau(tableau);
}

// Function to display the tableau
function displayTableau(tableau) {
    const tableContainer = document.getElementById("iteration_tables");
    const table = document.createElement("table");

    tableau.forEach(rowData => {
        const row = document.createElement("tr");
        for (const variable in rowData) {
            const cell = document.createElement("td");
            cell.textContent = rowData[variable];
            row.appendChild(cell);
        }
        table.appendChild(row);
    });

    tableContainer.appendChild(table);
}

// Function to select the pivot column
function selectPivotColumn(tableau) {
    const minCoefficient = Math.min(...Object.values(tableau[0]).slice(1));
    return minCoefficient < 0 ? Object.keys(tableau[0]).find(key => tableau[0][key] === minCoefficient) : null;
}

// Function to select the pivot row
function selectPivotRow(tableau, pivotColumn) {
    let minRatio = Infinity;
    let pivotRow = null;

    for (let i = 1; i < tableau.length; i++) {
        if (tableau[i][pivotColumn] > 0) {
            const ratio = tableau[i].constant / tableau[i][pivotColumn];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }

    return pivotRow;
}

// Function to perform Gaussian elimination
function gaussianElimination(tableau, pivotRow, pivotColumn) {
    const pivotValue = tableau[pivotRow][pivotColumn];

    // Divide pivot row by pivot value
    for (const variable in tableau[pivotRow]) {
        tableau[pivotRow][variable] /= pivotValue;
    }

    // Perform row operations
    for (let i = 0; i < tableau.length; i++) {
        if (i !== pivotRow) {
            const multiplier = tableau[i][pivotColumn];
            for (const variable in tableau[i]) {
                tableau[i][variable] -= multiplier * tableau[pivotRow][variable];
            }
        }
    }
}
