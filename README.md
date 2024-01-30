Programación 2 
===============

Este curso vamos a utilizar Git y GitHub para hacer un seguimiento de tu
trabajo en las prácticas de la asignatura. Git es una herramienta para el
control de versiones de software, que se basa en la idea de tener un
repositorio en un directorio oculto (llamado .git) para guardar las diferentes 
versiones de un programa más o menos grande. Aunque es una herramienta muy
potente (pensada para el desarrollo de software en equipo), vamos a usar
solamente una mínima parte de su potencial. GitHub es una web que permite
alojar repositorios públicos o privados (en la asignatura usaremos solamente
repositorios privados), y se integra perfectamente con Git.



Primer paso (sólo hay que hacerlo una vez)
==========================================

1. Crear usuario en GitHub (https://github.com > Sign up)
  con tu email de la UA  (p.ej. xxx99@alu.ua.es), con usuario 'xxx99-ua'
  (pon tu usuario en vez de 'xxx99')

2. Crear un nuevo repositorio (New repository) privado llamado 
   p2-00000000 (pon tu DNI/NIE sin letras en vez de 00000000)

3. Invita a tu profesor de prácticas como colaborador:
  - Entra en el repositorio, pestaña "Settings", opción "Manage access", botón
    "Invite a collaborator"  y pon el usuario de GitHub de tu profesor para
   que GitHub le mande una invitación

4. Desde la pestaña "Code", importa el repositorio básico de la asignatura:
  - Botón "Import code"
  - En "Your old repository's close URL" pon
    https://github.com/paco-dlsi/p2-template.git

5. Crea un "Personal access token"
  - Pincha en el usuario (arriba a la derecha), luego en "Settings", luego
   en "Developer settings" y en "Personal access tokens"
  - Crea un nuevo token
    + pon una nota indicando para qué es (prácticas Programación 2, p.ej.)
    + En "Expiration", elige "No expiration"
    + En "Select scopes", marca la opción "repo"
    + Abajo del todo, pincha en el botón "Generate token"
    + Guarda el token en un fichero seguro, debes usarlo como contraseña 
     cuando 'git' te la pida

5. Crea una copia local de tu repositorio
  - Abre un terminal en tu ordenador y crea un directorio para tus prácticas 
   de Programación 2 (p.ej. /home/paco/p2-2021):

   $ mkdir p2-2022

  - Bájate el repositorio que has creado

   $ cd p2-2022

   $ git clone https://github.com/xxx99-ua/p2-00000000

    (donde 'xxx99' es tu email de la UA, y '00000000' tu DNI)
    Te pedirá usuario (xxx99) y contraseña (el "Personal access token")

6. Configura el repositorio para guardar tu nombre de usuario y tu email:

   $ git config --global user.name xxx99-ua

   $ git config --global user.email xxx99@alu.ua.es


