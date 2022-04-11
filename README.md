# Projekt 1 - Ověřování síly hesel (práce s textem)

## Motivace projektu

Snad všichni známe tu situaci, kdy si chceme vytvořit nové heslo do nějakého systému, ale ten nás pořád otravuje nesmyslnými požadavky na formát hesla. I když jednoduchá kombinatorika říka, že většina těchto pravidel je zbytečná a nejbezpečnější je prostě vytvořit dostatečně dlouhé heslo, pravidla pořád existují a uživatelé se s nimi musí naučit žít. V tomto projektu se na daný problém podíváme z opačné strany, konkrétně si vyzkoušíme, jak takový jednoduchý systém ověřující sílu hesel naprogramovat.

## Popis projektu

Cílem projektu je vytvořit program, který na vstupu dostane sadu hesel a pro každé z nich ověří, jestli heslo splňuje všechna (pevně zadaná) požadovaná pravidla. Ta hesla, která projdou kontrolou, budou vypisována na výstup, ostatní budou zahozena.

## Detailní specifikace

Program implementujte ve zdrojovém souboru "pwcheck.c". Vstupní data (seznam hesel) budou čtena ze standardního vstupu (stdin), výstup (filtrovaný seznam hesel) bude tisknut na standardní výstup (stdout).

### Překlad a odevzdání zdrojového souboru

Odevzdání: Odevzdejte zdrojový soubor ''pwcheck.c'' prostřednictvím informačního systému.

Překlad: Program překládejte s následujícími argumenty:

<pre>$ gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck </pre>

### Syntax spuštění

Program se spouští v následující podobě: (./pwcheck značí umístění a název programu):

<pre>./pwcheck LEVEL PARAM [--stats] </pre>

Program je spouštěn se dvěma pevně zadanými argumenty <code>LEVEL</code> a <code>PARAM</code> a s jedním volitelným argumentem <code>--stats</code>, případně zadaným na třetí pozici:
; <code>LEVEL</code>
: celé číslo v intervalu &lbrack;1, 4&rbrack;, které určuje požadovanou ''úroveň bezpečnosti'' (viz níže)
; <code>PARAM</code>
: kladné celé číslo, které určuje dodatečný ''parametr pravidel'' (viz níže)
; <code>--stats</code>
: pokud je zadané, určuje, zda se na konci programu mají vypsat souhrnné statistiky analyzovaných hesel

### Úrovně bezpečnosti (kontrolovaná pravidla)

Jsou definovány celkem 4 úrovně bezpečnosti vyjádřeny pomocí 4 pravidel. Úroveň bezpečnosti určuje, že hesla musí splňovat všechna pravidla na dané a nižší úrovni. Tzn. např. úroveň bezpečnosti 3 specifikuje, že hesla musí splňovat pravidla 1, 2 a 3.

Některá pravidla jsou parametrizovatelná celým číslem zadaným pomocí argumentu programu <code>PARAM</code>. V následujícím seznamu je tento parametr označen jako X.

Seznam pravidel:
- Heslo obsahuje alespoň 1 velké a 1 malé písmeno.
- Heslo obsahuje znaky z alespoň X skupin <span style="color:blue">(v případě, že je číslo X větší než 4, myslí se tím všechny skupiny)</span>. Uvažované skupiny jsou:
#* malá písmena (a-z)
#* velká písmena (A-Z)
#* čísla (0-9)
#* speciální znaky (podporované musí být alespoň nealfanumerické znaky z ASCII tabulky na pozicích <span style="text-decoration:line-through;color:gray">33-126</span> <span style="color:red">32-126, tedy včetně mezery</span>)
- Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
- Heslo neobsahuje dva stejné podřetězce délky alespoň X.

### Statistiky

Pokud je zadaný argument programu <code>--stats</code>, program musí na konec výstupu vypsat celkové statistiky ve formátu:
<pre>
Statistika:
Ruznych znaku: NCHARS
Minimalni delka: MIN
Prumerna delka: AVG
</pre>
kde <code>NCHARS</code> je ''počet různých znaků'' vyskytujících se napříč všemi hesly, <code>MIN</code> je ''délka nejkratšího hesla'' (resp. hesel) a <code>AVG</code> je ''průměrná délka hesla'' (aritmetický průměr) zaokrouhlená na 1 desetiné místo. Statistiky zahrňují i hesla, která byla zahozena.

## Implementační detaily

### Vstupní data (seznam hesel)

Seznam hesel je programu předán na standardním vstupu (stdin). Každé heslo je zadáno na samostatném řádku a obsahuje pouze ASCII textová data, kromě znaku nového řádku. Maximální délka hesla je 100 znaků, jinak se jedná o nevalidní data. Program musí podporovat neomezený počet hesel na vstupu.

### Výstup programu

Program na standardní výstup (stdout) vypisuje hesla ze vstupního seznamu, každé na samostatný řádek, která splňují požadovanou úroveň bezpečnosti zadanou jako argument programu <code>LEVEL</code>. Hesla musí být vypsána beze změny a ve stejném pořadí, v jakém se objevila na vstupu.

Za výstupním seznamem hesel pak program volitelně vypisuje statistiku (viz. [[#Statistiky]]).

### Omezení v projektu

Je zakázané použít následující funkce:

* volání funkcí z knihoven <code>string.h</code> a <code>ctype.h</code> - cílem projektu je naučit se implementovat dané funkce ručně,
* volání z rodiny <code>malloc</code> a <code>free</code> - práce s dynamickou pamětí není v tomto projektu zapotřebí,
* volání z rodiny <code>fopen</code>, <code>fclose</code>, <code>fscanf</code>, ... - práce se soubory (dočasnými) není v tomto projektu žádoucí,
* volání funkce <code>exit</code> - cílem projektu je naučit se vytvořit programové konstrukce, které dokáží zpracovat neočekávaný stav programu a případně program řádně ukončit návratem z funkce main.

<span style="color:blue">Program musí vyhovovat standardu ISO C99. Jsou povoleny pouze hlavičkové soubory: <code>stdio.h</code>, <code>stdlib.h</code>, <code>stdbool.h</code> a případně (není nutné pro funkcionalitu) <code>assert.h</code>, <code>errno.h</code> a <code>limits.h</code>.</span>

### Neočekávané chování

Na chyby za běhu programu reagujte obvyklým způsobem: na neočekávaná vstupní data, formát vstupních dat nebo chyby při volání funkcí reagujte přerušením programu se stručným a výstižným chybovým hlášením na příslušný výstup a odpovídajícím návratovým kódem. Hlášení budou v kódování ASCII česky nebo anglicky.

## Hodnocení

<span style="color:blue">Funkcionalita vašeho programu bude hodnocena na strojích s operačním systémem GNU Linux.</span>

Na výsledné hodnocení mají hlavní vliv následující faktory:

* přeložitelnost zdrojového souboru,
* formát zdrojového souboru (členění, zarovnání, komentáře, vhodně zvolené identifikátory),
* dekompozice problému na podproblémy (vhodné funkce, vhodná délka funkcí a parametry funkcí),
* správná volba datových typů, případně tvorba nových typů,
* správná funkcionalita filtrování hesel,
* ošetření chybových stavů.

### Priority funkcionality

# Detekce jednotlivých pravidel: jelikož každá úroveň zabezpečení vyžaduje ověření všech pravidel nižší úrovně, dává smysl jednotlivá pravidla implementovat v pořadí, jak jsou zadána.
# Vypisování statistik.
# Další (prémiové) rozšíření funkcionality.

### Prémiové řešení

Prémiové řešení je dobrovolné a lze za něj získat bonusové body. Podmínkou pro udělení prémiových bodů je výborné vypracování povinných částí projektu zadání. Výsledné hodnocení je plně v kompetenci vyučujího, který bude projekt hodnotit. Výše prémiových bodů závisí také na sofistikovanosti řešení.

Navrhované rozšíření:
* Pokročilé načítání argumentů příkazové řádky (až 1 bod): program nevyžaduje argumenty pouze na pevných pozicích, ale je možné zadat úroveň zabezpečení a parametr pravidel také pomocí volitelných přepínačů. Syntax spuštění:
<pre>./pwcheck [-l LEVEL] [-p PARAM] [--stats]</pre>
přičemž jednotlivé přepínače mohou být zadány v libovolném pořadí. Při nezadání přepínače je výchozí hodnota příslušného argumentu 1. Upozornění: program v rozšířené formě musí stále akceptovat argumenty příkazové řádky původní, nerozšířené varianty: <pre>./pwcheck LEVEL PARAM [--stats]</pre>
