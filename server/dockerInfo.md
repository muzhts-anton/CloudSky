## Информация по тому, как запускать Dockerfile в текущем проекте

Сначала находясь в /server/lib/ServerConnection 
```bash
docker build -t <imageName> .
```
Затем
```bash
docker run --rm --net=host -it -p 127.0.0.1:8050:8080 <imageName>
```

Названия портов можно менять (**но** тогда не забыть поменять и в коде - пока порты определяются в main)

## Для IP
Внутренний IP:
```bash
sudo ifconfig
```

Внешний IP:
```bash
https://ifconfig.me/
```


