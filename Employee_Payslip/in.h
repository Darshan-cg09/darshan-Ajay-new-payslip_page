<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Employee Payslip Viewer</title>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
    <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css" rel="stylesheet">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/html2canvas/1.4.1/html2canvas.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jspdf/2.5.1/jspdf.umd.min.js"></script>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Roboto', sans-serif;
        }

        body {
            background-color: #f5f5f5;
            padding: 20px;
        }

        .container {
            max-width: 1200px;
            margin: 0 auto;
            background-color: #fff;
            padding: 30px;
            border-bottom-left-radius: 10px;
            border-bottom-right-radius: 10px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1);
        }

        header {
            max-width: 1200px;
            margin: 0 auto;
            background-color: #2c53ff;
            padding: 30px;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1);
        }

        h1 {
            color: #ffffff;
            font-size: 30px;
            text-align: center;
            font-weight: 700;
            letter-spacing: 1px;
        }

        .form-container {
            background-color: #f9f9f9;
            padding: 20px;
            border-radius: 8px;
            margin-bottom: 30px;
            border: 1px solid #e0e0e0;
        }

        .form-row {
            display: flex;
            flex-wrap: wrap;
            gap: 15px;
            align-items: flex-end;
        }

        .form-group {
            flex: 1;
            min-width: 200px;
        }

        label {
            display: block;
            margin-bottom: 8px;
            font-weight: 500;
            color: #34495e;
            font-size: 14px;
        }

        input, select {
            width: 100%;
            padding: 10px;
            border: 1px solid #d0d0d0;
            border-radius: 4px;
            font-size: 14px;
            transition: border-color 0.3s;
        }

        input:focus, select:focus {
            border-color: #3498db;
            outline: none;
        }

        .buttons {
            display: flex;
            justify-content: space-between;
            margin-top: 20px;
        }

        .btn {
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-weight: 500;
            transition: background-color 0.3s, transform 0.1s;
            height: 40px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
        }

        .btn-view {
            background-color: #2c53ff;
            color: white;
        }

        .btn-view:hover {
            background-color: #2980b9;
            transform: translateY(-1px);
        }

        .btn-download {
            background-color: #2ecc71;
            color: white;
        }

        .btn-download:hover {
            background-color: #27ae60;
            transform: translateY(-1px);
        }

        .btn-close {
            background-color: #e74c3c;
            color: white;
        }

        .btn-close:hover {
            background-color: #c0392b;
            transform: translateY(-1px);
        }

        .notification {
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 4px;
            color: white;
            display: none;
        }

        .success {
            background-color: #2ecc71;
        }

        .error {
            background-color: #e74c3c;
        }

        .error-message {
            color: #e74c3c;
            font-size: 12px;
        }

        .preview-container {
            display: none;
            margin-top: 30px;
        }

        .no-results {
            display: none;
            text-align: center;
            padding: 20px;
            background-color: #f8f8f8;
            border-radius: 5px;
            color: #666;
        }

        .payslip {
            border: 1px solid #d0d0d0;
            border-radius: 8px;
            background-color: white;
            padding: 25px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.05);
            width: 100%;
            max-width: 200mm;
            margin: 0 auto;
            box-sizing: border-box;
        }

        .payslip-header .header-top {
            display: flex;
            align-items: center;
            justify-content: space-between;
            margin-bottom: 20px;
            padding-bottom: 15px;
            border-bottom: 2px solid #e0e0e0;
        }

        .company-logo {
            width: 180px;
            height: 100px;
            border-radius: 10px;
            object-fit: contain;
            background-color: #f9f9f9;
        }

        .company-details {
            text-align: right;
            max-width: 50%;
        }

        .company-details h2 {
            font-size: 22px;
            margin-bottom: 8px;
            color: #2c3e50;
            overflow-wrap: break-word;
            line-height: 1.4;
        }

        .company-details p {
            font-size: 12px;
            color: #7f8c8d;
            line-height: 1.5;
        }

        .payslip-header h3 {
            text-align: center;
            margin-top: 10px;
            color: #34495e;
            font-size: 20px;
            font-weight: 600;
            text-transform: uppercase;
        }

        .payslip-details .details-table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 20px;
        }

        .payslip-details .details-table td {
            padding: 10px;
            font-size: 14px;
            border: 1px solid #d0d0d0;
            color: #2c3e50;
        }

        .detail-label {
            font-weight: 500;
            color: #34495e;
        }

        .earnings-deductions {
            display: flex;
            gap: 20px;
            margin-top: 20px;
        }

        .earnings, .deductions {
            flex: 1;
            background-color: #fff;
            border: 1px solid #d0d0d0;
            border-radius: 5px;
        }

        .payslip-table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 15px;
        }

        .payslip-table th, .payslip-table td {
            padding: 10px;
            text-align: left;
            border: 1px solid #d0d0d0;
            font-size: 14px;
        }

        .payslip-table th {
            background-color: #ecf0f1;
            font-weight: 600;
            color: #34495e;
        }

        .payslip-table tbody tr:nth-child(even) {
            background-color: #f9f9f9;
        }

        .payslip-table tfoot td {
            font-weight: 500;
            background-color: #ecf0f1;
        }

        .payslip-total {
            text-align: left;
            font-weight: 500;
            margin-top: 20px;
            font-size: 16px;
            color: #2c3e50;
        }

        #preview-amount-in-words {
            margin-top: 10px;
            font-style: italic;
            font-size: 14px;
            color: #7f8c8d;
        }

        .payslip-footer {
            margin-top: 30px;
            text-align: center;
            font-size: 12px;
            color: #7f8c8d;
            padding-top: 10px;
            border-top: 1px solid #e0e0e0;
        }

        @media (max-width: 768px) {
            .form-row {
                flex-direction: column;
            }
            
            .form-group {
                width: 100%;
            }
            
            .earnings-deductions {
                flex-direction: column;
            }
            
            .earnings, .deductions {
                width: 100%;
            }

            .payslip-header .header-top {
                flex-direction: column;
                align-items: flex-start;
            }

            .company-details {
                text-align: left;
                margin-top: 15px;
                max-width: 100%;
            }

            .company-logo {
                width: 150px;
                height: 80px;
            }
        }
    </style>
</head>
<body>
    <header>
        <h1>EMPLOYEE PAYSLIP VIEWER</h1>
    </header>
    <div class="container">
        <div class="notification success" id="success-notification"></div>
        <div class="notification error" id="error-notification"></div>

        <div class="form-container" id="form-container">
            <div class="form-row">
                <div class="form-group">
                    <label for="employee-id">Employee ID:</label>
                    <input type="text" id="employee-id" placeholder="e.g., ATS0123" maxlength="7">
                    <span class="error-message" id="employee-id-error"></span>
                </div>
                <div class="form-group">
                    <label for="month">Month:</label>
                    <select id="month">
                        <option value="">Select Month</option>
                        <option value="01">January</option>
                        <option value="02">February</option>
                        <option value="03">March</option>
                        <option value="04">April</option>
                        <option value="05">May</option>
                        <option value="06">June</option>
                        <option value="07">July</option>
                        <option value="08">August</option>
                        <option value="09">September</option>
                        <option value="10">October</option>
                        <option value="11">November</option>
                        <option value="12">December</option>
                    </select>
                    <span class="error-message" id="month-error"></span>
                </div>
                <div class="form-group">
                    <label for="year">Year:</label>
                    <select id="year">
                        <option value="">Select Year</option>
                        <!-- Dynamically populated -->
                    </select>
                    <span class="error-message" id="year-error"></span>
                </div>
            </div>
            <div class="buttons" style="justify-content: center;">
                <button type="button" class="btn btn-view" id="view-payslip">View Payslip</button>
            </div>
        </div>

        <div class="no-results" id="no-results">
            <div class="no-records-icon">
                <i class="fas fa-folder-open"></i>
            </div>
            <h3>No payslips found for the selected criteria</h3>
            <p>Please check your Employee ID and try a different month/year, or contact HR for assistance.</p>
        </div>

        <div class="preview-container" id="preview-container">
            <div class="payslip">
                <div class="payslip-header">
                    <div class="header-top">
                        <!-- Replace with Base64 string: data:image/jpeg;base64,/9j/4AAQ... -->
                        <img src="/ATS_Wallpaper.jpg" alt="ATS Logo" class="company-logo" />
                        <div class="company-details">
                            <h2>Astrolite Tech Solutions Pvt Ltd</h2>
                            <p>Plot No 65, Flat No 201, 2nd Floor, Siddivinayaka Nagar, Survey of India, Madhapur, HYDERABAD -081</p>
                        </div>
                    </div>
                    <h3>Salary Slip for <span id="preview-month-year"></span></h3>
                </div>

                <div class="payslip-details">
                    <table class="details-table">
                        <tr>
                            <td><span class="detail-label">Employee Name:</span> <span id="preview-name"></span></td>
                            <td><span class="detail-label">Employee Type:</span> <span id="preview-type"></span><span class="detail-label" style="border-left:2px solid #9e9e9e;padding-left: 5px; margin-left: 5px;">Employee Code:</span> <span id="preview-id"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">Designation:</span> <span id="preview-designation"></span></td>
                            <td><span class="detail-label">Duration:</span> <span id="preview-duration"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">Date of Joining:</span> <span id="preview-doj"></span></td>
                            <td><span class="detail-label">No of Days in the Month:</span> <span id="preview-working-days"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">Current Office Location:</span> <span id="preview-location"></span></td>
                            <td><span class="detail-label">Working Days:</span> <span id="preview-working-days-actual"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">Bank Name:</span> <span id="preview-bank"></span></td>
                            <td><span class="detail-label">Arrear Days:</span> <span id="preview-arrear-days"></span><span class="detail-label" style="border-left:2px solid #9e9e9e;padding-left: 5px; margin-left: 5px;">LOP:</span> <span id="preview-lop"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">Bank Account No:</span> <span id="preview-account"></span></td>
                            <td><span class="detail-label">PAN No:</span> <span id="preview-pan"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">Provident Fund:</span> <span id="preview-pf"></span></td>
                            <td><span class="detail-label">ESIC Number:</span> <span id="preview-esic"></span></td>
                        </tr>
                        <tr>
                            <td><span class="detail-label">UAN No:</span> <span id="preview-uan"></span></td>
                            <td></td>
                        </tr>
                    </table>
                </div>

                <div class="earnings-deductions">
                    <div class="earnings">
                        <table class="payslip-table">
                            <thead>
                                <tr>
                                    <th>Components</th>
                                    <th>Amount (Rs.)</th>
                                </tr>
                            </thead>
                            <tbody id="preview-earnings-table"></tbody>
                            <tfoot>
                                <tr>
                                    <td><strong>Gross Pay (A)</strong></td>
                                    <td><strong id="preview-gross-pay">0</strong></td>
                                </tr>
                            </tfoot>
                        </table>
                    </div>
                    <div class="deductions">
                        <table class="payslip-table">
                            <thead>
                                <tr>
                                    <th>Common Deductions</th>
                                    <th>Amount (Rs.)</th>
                                </tr>
                            </thead>
                            <tbody id="preview-deductions-table"></tbody>
                            <tfoot>
                                <tr>
                                    <td><strong>Total Deductions (B)</strong></td>
                                    <td><strong id="preview-total-deductions">0</strong></td>
                                </tr>
                            </tfoot>
                        </table>
                    </div>
                </div>

                <div class="payslip-total">
                    Net Pay (A - B): <span id="preview-net-pay">0</span>
                </div>

                <div id="preview-amount-in-words"></div>

                <div class="payslip-footer">
                    <p>Note: This is a Computer-Generated Slip and does not require signature</p>
                </div>

                <div class="buttons">
                    <button type="button" class="btn btn-close" id="back-to-form">Close</button>
                    <button type="button" class="btn btn-download" id="download-payslip">Download PDF</button>
                </div>
            </div>
        </div>
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            console.log('DOM loaded, initializing payslip viewer');

            // Check if page is loaded via file:// protocol
            if (window.location.protocol === 'file:') {
                showNotification('error', 'This application must be run via the server. Please open http://13.60.26.108:3018/Employee_Payslip instead of the local file.');
                const logoImg = document.querySelector('.company-logo');
                logoImg.src = 'https://placehold.co/180x100?text=Logo';
                console.log('Forced placeholder due to file:// protocol:', logoImg.src);
            }

            // Hide preview container by default
            document.getElementById('preview-container').style.display = 'none';
            document.getElementById('no-results').style.display = 'none';

            // Populate year dropdown
            const yearSelect = document.getElementById('year');
            const currentYear = new Date().getFullYear();
            for (let year = currentYear; year >= currentYear - 5; year--) {
                const option = document.createElement('option');
                option.value = year;
                option.textContent = year;
                yearSelect.appendChild(option);
            }

            // Setup logo event handlers
            const logoImg = document.querySelector('.company-logo');
            console.log('Setting logo src:', logoImg.src);
            logoImg.addEventListener('load', function() {
                console.log('Logo loaded successfully:', logoImg.src);
            });
            logoImg.addEventListener('error', function(event) {
                console.error('Logo failed to load:', logoImg.src, 'Error:', event);
                showNotification('error', 'Failed to load logo. Using placeholder image. Please ensure the server is running and access via http://13.60.26.108:3018/Employee_Payslip.');
                logoImg.src = 'https://placehold.co/180x100?text=Logo';
                console.log('Switched to placeholder:', logoImg.src);
            });
            console.log('Logo event handlers set up');

            // Setup Input Restrictions and Real-time Validation
            function setupInputRestrictions() {
                console.log('Setting up input restrictions');
                const employeeIdInput = document.getElementById('employee-id');
                employeeIdInput.addEventListener('input', function(e) {
                    let value = e.target.value.replace(/[^A-Z0-9]/g, '').toUpperCase();
                    value = value.slice(0, 7);
                    e.target.value = value;

                    const errorElement = document.getElementById('employee-id-error');
                    if (!validateEmployeeId(value)) {
                        errorElement.textContent = 'Must start with ATS0 followed by 3 digits (not 000)';
                    } else {
                        errorElement.textContent = '';
                    }
                });

                document.getElementById('month').addEventListener('change', function(e) {
                    const errorElement = document.getElementById('month-error');
                    if (!e.target.value) {
                        errorElement.textContent = 'Month is required';
                    } else {
                        errorElement.textContent = '';
                    }
                });

                document.getElementById('year').addEventListener('change', function(e) {
                    const errorElement = document.getElementById('year-error');
                    if (!e.target.value) {
                        errorElement.textContent = 'Year is required';
                    } else {
                        errorElement.textContent = '';
                    }
                });
            }

            setupInputRestrictions();

            document.getElementById('view-payslip').addEventListener('click', viewPayslip);
            document.getElementById('download-payslip').addEventListener('click', downloadPayslip);
            document.getElementById('back-to-form').addEventListener('click', backToForm);

            function validateEmployeeId(id) {
                const employeeIdRegex = /^ATS0(?!000)\d{3}$/;
                return employeeIdRegex.test(id.trim());
            }

            function validateForm() {
                console.log('Validating form');
                let isValid = true;
                document.getElementById('error-notification').style.display = 'none';

                const employeeId = document.getElementById('employee-id').value;
                const month = document.getElementById('month').value;
                const year = document.getElementById('year').value;

                const employeeIdError = document.getElementById('employee-id-error');
                if (!validateEmployeeId(employeeId)) {
                    employeeIdError.textContent = 'Must start with ATS0 followed by 3 digits (not 000)';
                    isValid = false;
                } else {
                    employeeIdError.textContent = '';
                }

                const monthError = document.getElementById('month-error');
                if (!month) {
                    monthError.textContent = 'Month is required';
                    isValid = false;
                } else {
                    monthError.textContent = '';
                }

                const yearError = document.getElementById('year-error');
                if (!year) {
                    yearError.textContent = 'Year is required';
                    isValid = false;
                } else {
                    yearError.textContent = '';
                }

                if (!isValid) {
                    document.getElementById('error-notification').textContent = 'Please correct the highlighted errors';
                    document.getElementById('error-notification').style.display = 'block';
                }

                return isValid;
            }

            async function viewPayslip() {
                console.log('View payslip clicked');
                if (validateForm()) {
                    const employeeId = document.getElementById('employee-id').value;
                    const month = document.getElementById('month').value;
                    const year = document.getElementById('year').value;

                    try {
                        const response = await fetch('http://13.60.26.108:3018/api/payslips?employeeId=' + employeeId + '&month=' + month + '&year=' + year);
                        if (!response.ok) {
                            throw new Error((await response.json()).error || 'Failed to fetch payslip');
                        }
                        const payslip = await response.json();
                        populatePreview(payslip);
                        document.getElementById('form-container').style.display = 'none';
                        document.getElementById('no-results').style.display = 'none';
                        document.getElementById('preview-container').style.display = 'block';
                    } catch (error) {
                        console.error('Error fetching payslip:', error);
                        showNotification('error', error.message || 'Failed to fetch payslip');
                        document.getElementById('no-results').style.display = 'block';
                        document.getElementById('preview-container').style.display = 'none';
                    }
                }
            }

            function backToForm() {
                console.log('Back to form clicked');
                document.getElementById('preview-container').style.display = 'none';
                document.getElementById('no-results').style.display = 'none';
                document.getElementById('form-container').style.display = 'block';
            }

            function generateCanvas(payslipElement, callback, errorCallback) {
                console.log('Generating canvas');
                try {
                    html2canvas(payslipElement, {
                        scale: 2,
                        useCORS: true,
                        logging: true,
                        backgroundColor: '#ffffff'
                    }).then(function(canvas) {
                        console.log('Canvas generated successfully');
                        callback(canvas);
                    }).catch(function(error) {
                        console.error('Error generating canvas:', error);
                        errorCallback(error);
                    });
                } catch (error) {
                    console.error('Error in generateCanvas:', error);
                    errorCallback(error);
                }
            }

            function createPDF(canvas, monthYear) {
                console.log('Creating PDF for:', monthYear);
                try {
                    const jsPDF = window.jspdf.jsPDF;
                    const doc = new jsPDF({
                        orientation: 'portrait',
                        unit: 'mm',
                        format: 'a4',
                        compress: true
                    });

                    const imgData = canvas.toDataURL('image/png', 1.0);
                    const pdfWidth = doc.internal.pageSize.getWidth();
                    const pdfHeight = doc.internal.pageSize.getHeight();
                    const imgProps = doc.getImageProperties(imgData);
                    const imgHeight = (imgProps.height * pdfWidth) / imgProps.width;

                    let heightLeft = imgHeight;
                    let position = 0;

                    while (heightLeft > 0) {
                        doc.addImage(imgData, 'PNG', 0, position, pdfWidth, imgHeight);
                        heightLeft = heightLeft - pdfHeight;
                        position = position - pdfHeight;
                        if (heightLeft > 0) {
                            doc.addPage();
                        }
                    }

                    doc.save('Payslip_' + monthYear.replace(/\s+/g, '_') + '.pdf');
                    console.log('PDF saved successfully');
                } catch (error) {
                    console.error('Error in createPDF:', error);
                    throw error;
                }
            }

            function downloadPayslip() {
    console.log('Download payslip started');
    const downloadButton = document.getElementById('download-payslip');
    downloadButton.disabled = true;
    downloadButton.textContent = 'Generating PDF...';

    try {
        if (!window.jspdf || !window.jspdf.jsPDF || !window.html2canvas) {
            console.error('Libraries missing');
            showNotification('error', 'Required libraries (jsPDF or html2canvas) not loaded. Please try again later.');
            downloadButton.disabled = false;
            downloadButton.textContent = 'Download PDF';
            return;
        }

        const payslipElement = document.querySelector('.payslip');
        const buttonsDiv = payslipElement.querySelector('.buttons'); // Select the buttons div
        const monthYear = document.getElementById('preview-month-year').textContent || 'Unknown';

        if (!payslipElement) {
            console.error('Payslip element not found');
            showNotification('error', 'Payslip content not found. Please try again.');
            downloadButton.disabled = false;
            downloadButton.textContent = 'Download PDF';
            return;
        }

        // Hide buttons before generating the canvas
        if (buttonsDiv) {
            buttonsDiv.style.display = 'none';
        }

        const logoImg = payslipElement.querySelector('.company-logo');
        console.log('Preloading logo for PDF:', logoImg.src);
        const preloadImg = new Image();
        preloadImg.crossOrigin = 'Anonymous';
        preloadImg.src = logoImg.src;

        preloadImg.onload = function() {
            console.log('Logo preloaded for PDF:', logoImg.src);
            setTimeout(function() {
                console.log('Generating canvas after delay');
                generateCanvas(
                    payslipElement,
                    function(canvas) {
                        console.log('Canvas ready, creating PDF');
                        createPDF(canvas, monthYear);
                        // Show buttons again after PDF is generated
                        if (buttonsDiv) {
                            buttonsDiv.style.display = '';
                        }
                        downloadButton.disabled = false;
                        downloadButton.textContent = 'Download PDF';
                    },
                    function(error) {
                        console.error('Canvas generation failed:', error);
                        showNotification('error', 'Failed to generate PDF due to image loading issues.');
                        // Show buttons again in case of error
                        if (buttonsDiv) {
                            buttonsDiv.style.display = '';
                        }
                        downloadButton.disabled = false;
                        downloadButton.textContent = 'Download PDF';
                    }
                );
            }, 500);
        };

        preloadImg.onerror = function(event) {
            console.warn('Logo preload failed:', logoImg.src, 'Error:', event);
            showNotification('error', 'Failed to load logo for PDF. Using placeholder. Please ensure server is running.');
            logoImg.src = 'https://placehold.co/180x100?text=Logo';
            console.log('Switched to placeholder for PDF:', logoImg.src);
            const fallbackImg = new Image();
            fallbackImg.crossOrigin = 'Anonymous';
            fallbackImg.src = logoImg.src;

            fallbackImg.onload = function() {
                console.log('Fallback logo loaded:', logoImg.src);
                setTimeout(function() {
                    console.log('Generating canvas with fallback');
                    generateCanvas(
                        payslipElement,
                        function(canvas) {
                            console.log('Canvas ready, creating PDF with fallback');
                            createPDF(canvas, monthYear);
                            // Show buttons again after PDF is generated
                            if (buttonsDiv) {
                                buttonsDiv.style.display = '';
                            }
                            downloadButton.disabled = false;
                            downloadButton.textContent = 'Download PDF';
                        },
                        function(error) {
                            console.error('Fallback canvas failed:', error);
                            showNotification('error', 'Failed to generate PDF with fallback image. Generating without logo.');
                            logoImg.style.display = 'none';
                            generateCanvas(
                                payslipElement,
                                function(canvas) {
                                    console.log('Canvas ready, creating PDF without logo');
                                    createPDF(canvas, monthYear);
                                    logoImg.style.display = '';
                                    // Show buttons again after PDF is generated
                                    if (buttonsDiv) {
                                        buttonsDiv.style.display = '';
                                    }
                                    downloadButton.disabled = false;
                                    downloadButton.textContent = 'Download PDF';
                                },
                                function(error) {
                                    console.error('No-logo canvas failed:', error);
                                    showNotification('error', 'Failed to generate PDF. Please check your network.');
                                    logoImg.style.display = '';
                                    // Show buttons again in case of error
                                    if (buttonsDiv) {
                                        buttonsDiv.style.display = '';
                                    }
                                    downloadButton.disabled = false;
                                    downloadButton.textContent = 'Download PDF';
                                }
                            );
                        }
                    );
                }, 500);
            };

            fallbackImg.onerror = function(event) {
                console.warn('Fallback image failed:', event);
                showNotification('error', 'Image loading failed. Generating PDF without logo.');
                logoImg.style.display = 'none';
                generateCanvas(
                    payslipElement,
                    function(canvas) {
                        console.log('Canvas ready, creating PDF without logo');
                        createPDF(canvas, monthYear);
                        logoImg.style.display = '';
                        // Show buttons again after PDF is generated
                        if (buttonsDiv) {
                            buttonsDiv.style.display = '';
                        }
                        downloadButton.disabled = false;
                        downloadButton.textContent = 'Download PDF';
                    },
                    function(error) {
                        console.error('Final canvas attempt failed:', error);
                        showNotification('error', 'Failed to generate PDF. Please check your network.');
                        logoImg.style.display = '';
                        // Show buttons again in case of error
                        if (buttonsDiv) {
                            buttonsDiv.style.display = '';
                        }
                        downloadButton.disabled = false;
                        downloadButton.textContent = 'Download PDF';
                    }
                );
            };
        };
    } catch (error) {
        console.error('Error in downloadPayslip:', error);
        showNotification('error', 'Failed to generate PDF. Please try again.');
        downloadButton.disabled = false;
        downloadButton.textContent = 'Download PDF';
    }
    console.log('Download payslip completed');
}

            function showNotification(type, message) {
                console.log('Showing notification:', type, message);
                const notification = document.getElementById(type + '-notification');
                notification.textContent = message;
                notification.style.display = 'block';
                setTimeout(function() {
                    notification.style.display = 'none';
                }, 5000);
            }

            function populatePreview(payslip) {
                console.log('Populating preview');
                document.getElementById('preview-month-year').textContent = payslip.monthYearFormatted || 'N/A';
                document.getElementById('preview-name').textContent = payslip.employeeName || 'N/A';
                document.getElementById('preview-designation').textContent = payslip.designation || 'N/A';
                document.getElementById('preview-doj').textContent = formatDate(payslip.dateJoining) || 'N/A';
                document.getElementById('preview-bank').textContent = payslip.bankName || 'N/A';
                document.getElementById('preview-type').textContent = payslip.employeeType || 'N/A';
                document.getElementById('preview-duration').textContent = payslip.duration || 'N/A';
                document.getElementById('preview-working-days').textContent = payslip.daysInMonth || '0';
                document.getElementById('preview-working-days-actual').textContent = payslip.workingDays || '0';
                document.getElementById('preview-arrear-days').textContent = payslip.arrearDays || '0';
                document.getElementById('preview-account').textContent = payslip.accountNo || 'N/A';
                document.getElementById('preview-id').textContent = payslip.employeeId || 'N/A';
                document.getElementById('preview-location').textContent = payslip.location || 'N/A';
                document.getElementById('preview-lop').textContent = payslip.lop || '0';
                document.getElementById('preview-pan').textContent = payslip.pan || 'N/A';
                document.getElementById('preview-pf').textContent = payslip.providentFund || 'N/A';
                document.getElementById('preview-uan').textContent = payslip.uan || 'N/A';
                document.getElementById('preview-esic').textContent = payslip.esic || 'N/A';

                const earningsTable = document.getElementById('preview-earnings-table');
                earningsTable.innerHTML = '';
                (payslip.earnings || []).forEach(function(earning) {
                    const row = document.createElement('tr');
                    const component = earning.component || 'N/A';
                    const amount = Number(earning.amount || 0).toFixed(2);
                    row.innerHTML = '<td>' + component + '</td><td>' + amount + '</td>';
                    earningsTable.appendChild(row);
                });

                const deductionsTable = document.getElementById('preview-deductions-table');
                deductionsTable.innerHTML = '';
                (payslip.deductions || []).forEach(function(deduction) {
                    const row = document.createElement('tr');
                    const component = deduction.component || 'N/A';
                    const amount = Number(deduction.amount || 0).toFixed(2);
                    row.innerHTML = '<td>' + component + '</td><td>' + amount + '</td>';
                    deductionsTable.appendChild(row);
                });

                document.getElementById('preview-gross-pay').textContent = Number(payslip.grossPay || 0).toFixed(2);
                document.getElementById('preview-total-deductions').textContent = Number(payslip.totalDeductions || 0).toFixed(2);
                document.getElementById('preview-net-pay').textContent = Number(payslip.netPay || 0).toFixed(2);
                document.getElementById('preview-amount-in-words').textContent = numberToWords(payslip.netPay || 0) + ' Rupees only';
                console.log('Preview populated');
            }

            function formatDate(dateString) {
                console.log('Formatting date:', dateString);
                if (!dateString) return 'N/A';
                try {
                    const date = new Date(dateString);
                    if (isNaN(date.getTime())) return 'N/A';
                    const day = String(date.getDate()).padStart(2, '0');
                    const month = String(date.getMonth() + 1).padStart(2, '0');
                    const year = date.getFullYear();
                    return day + '.' + month + '.' + year;
                } catch (error) {
                    console.error('Error formatting date:', error);
                    return 'N/A';
                }
            }

            function numberToWords(number) {
                console.log('Converting number to words:', number);
                try {
                    const first = ['', 'One ', 'Two ', 'Three ', 'Four ', 'Five ', 'Six ', 'Seven ', 'Eight ', 'Nine ', 'Ten ',
                        'Eleven ', 'Twelve ', 'Thirteen ', 'Fourteen ', 'Fifteen ', 'Sixteen ', 'Seventeen ',
                        'Eighteen ', 'Nineteen '];
                    const tens = ['', '', 'Twenty', 'Thirty', 'Forty', 'Fifty', 'Sixty', 'Seventy', 'Eighty', 'Ninety'];
                    const scales = ['', 'Thousand ', 'Lakh ', 'Crore '];

                    if (!number || number < 0) return 'Zero';

                    const numStr = Number(number).toFixed(2);
                    const parts = numStr.split('.');
                    const wholePart = parseInt(parts[0]);
                    const decimalPart = parseInt(parts[1]);

                    function convertWholeNumber(num) {
                        if (num === 0) return '';

                        let words = '';

                        const hundreds = num % 1000;
                        if (hundreds > 0) {
                            if (hundreds < 20) {
                                words = first[hundreds] + ' ';
                            } else {
                                const tensValue = Math.floor(hundreds / 10) % 10;
                                const onesValue = hundreds % 10;
                                words = tens[tensValue] + (onesValue > 0 ? ' ' + first[onesValue] : '') + ' ';
                            }
                        }

                        num = Math.floor(num / 1000);
                        if (num > 0) {
                            const thousands = num % 100;
                            if (thousands > 0) {
                                if (thousands < 20) {
                                    words = first[thousands] + ' Thousand ' + words;
                                } else {
                                    const tensValue = Math.floor(thousands / 10) % 10;
                                    const onesValue = thousands % 10;
                                    words = tens[tensValue] + (onesValue > 0 ? ' ' + first[onesValue] : '') + ' Thousand ' + words;
                                }
                            }
                        }

                        num = Math.floor(num / 100);
                        if (num > 0) {
                            const lakhs = num % 100;
                            if (lakhs > 0) {
                                if (lakhs < 20) {
                                    words = first[lakhs] + ' Lakh ' + words;
                                } else {
                                    const tensValue = Math.floor(lakhs / 10) % 10;
                                    const onesValue = lakhs % 10;
                                    words = tens[tensValue] + (onesValue > 0 ? ' ' + first[onesValue] : '') + ' Lakh ' + words;
                                }
                            }
                        }

                        num = Math.floor(num / 100);
                        if (num > 0) {
                            if (num < 20) {
                                words = first[num] + ' Crore ' + words;
                            } else {
                                const tensValue = Math.floor(num / 10) % 10;
                                const onesValue = num % 10;
                                words = tens[tensValue] + (onesValue > 0 ? ' ' + first[onesValue] : '') + ' Crore ' + words;
                            }
                        }

                        return words.trim();
                    }

                    let result = convertWholeNumber(wholePart);

                    if (decimalPart > 0) {
                        result = result + ' and ';
                        if (decimalPart < 20) {
                            result = result + first[decimalPart];
                        } else {
                            const tensValue = Math.floor(decimalPart / 10);
                            const onesValue = decimalPart % 10;
                            result = result + tens[tensValue] + (onesValue > 0 ? ' ' + first[onesValue] : '');
                        }
                        result = result + ' Paise';
                    }

                    return result.trim() || 'Zero';
                } catch (error) {
                    console.error('Error converting number to words:', error);
                    return 'Zero';
                }
            }
        });
    </script>
</body>
</html>
