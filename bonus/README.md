# Documentation Teams

Cette documentation vous servira à comprendre le fonctionnement de notre Teams pour pouvoir l'utiliser avec votre entourage

# Table des matières

- [Serveur](#serveur)
    - [Lancement] (#lancement serveur)

    - [Code] (#code)

- [Client](#serveur)
    - [Lancement] (#lancement client)

    - [Commandes] (#commandes)

# Serveur

Documentation du serveur.

## Lancement serveur

Il faut, pour lancer Teams utiliser une librairie qui permet d'utiliser les commandes.

Exemple:
```
sudo cp ./libs/myteams/libmyteams.so /lib64
```

Cette commande permet de copier la librairie dans le /lib64 pour pouvopir ensuite utiliser Teams

Une fois la librairie chargée, le binaire peut être généré puis lancé avec un port en paramètre sur lequel les clients ce connecterons.

Grâce aux commandes suivantes:

```
make
./myteams_server 4242
```

## Code

Cette section explique les codes que le serveur renvoie.

```
200 Command okay.
- Commande lancé

220 Service ready for new user.
- Utilisateur bien connecté

400 Invalid arguments.
- Mauvais argument dans une commande

401 Unknown command.
- Commande inconnu

420 Too long username.
- Nom d'utilisateur trop long

430 Please login with /login.
- Nécessite une connection avant d'utiliser les commandes

500 An internal error occured.
- Une erreur est survenue coté serveur
```

# Client

Documentation du client.

## Lancement client

Il faut, pour lancer Teams utiliser une librairie qui permet d'utiliser les commandes.

Exemple:
```
sudo cp ./libs/myteams/libmyteams.so /lib64
```

Cette commande permet de copier la librairie dans le /lib64 pour pouvopir ensuite utiliser Teams

Une fois la librairie chargée, le binaire peut être généré puis lancé avec le port en paramètre sur lequel le serveur a été lancé.

Grâce aux commandes suivantes:

```
make
./myteams_cli 4242
```

## Commandes

Cette section va expliquer en détail le fonctionnement de chaques commandes.

```
/help
- Permet d'afficher toutes les commandes existantes.
```

```
/login nom_utilisateur
- Assigne le nom_utilisateur utilisé par le client.
```

```
/logout
- Déconnecte le client du serveur.
```

```
/users
- Récupère la list de tout les utilisateurs qui éxistes.
```

```
/user utilisateur_uuid
- Récupère les informations d'un utilisateur.
```

```
/send utilisateur_uuid message
- Envoie un message à un utilisateur.
```

```
/subscribe equipe_uuid
- Permet de s'abonner à une équipe.
```

```
/subscribed
- Liste toute les équipes auquelles le client est abonné.

/subscribed equipe_uuid
- Liste tout les clients abonnés à cette équipes.
```

```
/unsubscribe equipe_uuid
- Permet de se desabonner d'une équipe
```
