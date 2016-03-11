#!/bin/bash
uwsgi --static-map /css=css --static-map /js=js --ini handlers.ini
