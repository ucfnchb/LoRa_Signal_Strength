# Exploring and Analysing LoRa’s Signal Strength and Effective Range in Dense Urban Environments

## Project Overview
This repository contains the code, data, and documentation for the MSc dissertation titled "Exploring and Analyzing LoRa’s Signal Strength and Effective Range in Dense Urban Environments." The dissertation investigates the performance of LoRa (Long Range) technology in urban settings, with a focus on signal strength and effective range across various urban densities.

## Abstract
The research explores LoRa’s operational effectiveness in densely and sparsely built urban areas by analyzing 246 data points collected across multiple routes. The study confirms that LoRa’s signal strength diminishes with increasing distance from the gateway, with a maximum effective range of about 3 km in sparsely built areas, and approximately 1.2 km in densely built areas. Key factors influencing signal propagation, such as building density and architectural features, are discussed. An unexpected detection of a LoRa signal from a gateway 7.5 km away in a dense urban environment suggests potential for greater coverage under specific conditions.

## Contents of the Repository
Data: Collected LoRa signal strength and related geographical data.

Code: Scripts for data processing, TTN payload formatter, Arduino Sketch 

Documentation: Detailed explanations of the methodology, including route planned, site information ext.
Figures: Visual representations of the data, including maps, graphs, and tables illustrating the findings.

## Key Findings
Signal Strength vs. Distance: RSSI values decrease as the distance from the gateway increases, with urban density significantly impacting effective range.
Urban Density Impact: Densely built areas have a much-reduced effective range (approx. 1.2 km) compared to sparsely built areas (up to 3 km).
Unexpected Findings: Detection of a LoRa signal from a gateway 7.5 km away indicates potential for greater-than-expected range under certain conditions.

## How to Use This Repository
This section provides a detailed guide on how to navigate and utilize each component of the repository.

### Directory Structure
#### data:
Description:
Contains the raw data files used in the analysis. These files include measurements such as RSSI (Received Signal Strength Indicator), SNR (Signal-to-Noise Ratio), and geographic coordinates.

Files:
Lora data.csv: The primary dataset used for analyzing signal strength.

Usage: Load these CSV files into a data analysis tool like Python (Pandas) or Excel to explore and process the data.

#### Scripts: 
Description: 
Code: Scripts for data processing, TTN payload formatter, Arduino Sketch 

Files:MRK WAN 131O Arduino Sketch, TTN formatter, Telegraph Configeration 

Usage: Run these scripts in your local Arduino or Python environment or TTN platform to replicate the data processing steps.

#### Docs: 
Description:

Includes detailed documentation on the methodology, routes planned and geographical points planned used in the project.

Files: Routes Planning

Usage Refer to these documents for a comprehensive understanding of the research process and to replicate the study setup.

#### visualizations: 

Description: Contains the output visualizations generated by the Mapbox, QGIS, Google Earth, Grafana

Files:  visualization 

Usage: These visualizations can be used to interpret the findings and are essential for understanding the impact of urban density on LoRa signal strength.


#### By following these instructions and exploring the files in the repository, you can replicate the study, analyze the data, and build upon the research. This repository is designed to be user-friendly and comprehensive, making it an useful resource for exploring LoRa technology in urban environments.
