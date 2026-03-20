# Personal nutritionist

Summary: today you strengthen the skills acquired over the previous days.

## Foreword

Your organism as a system that needs to get different nutrients to live a happy
and effective life.
If it lacks nutrients, important chemical reactions may stop occurring and your
health will fall apart.
Diet should be balanced if you want to live healthily.
You need: proteins, carbohydrates, fats, *Fe*, *Mg*, *Na*, *K*, *Ca*, *Zn*,
*Se*, *Cr*, *I*, vitamins: *D*, *B12*, *E*, *C*, *A*, *K*, *Cu*.
If you do not eat protein, your body will start looking for them inside own
muscles, organs, tissues.
You will lack certain enzymes, hormones, transport proteins, immune cells.
If you eat too much, body will be intoxicated by decaying materials and health
will decrease.
This applies to any item in the list.
The first problem is that diet is not as diverse.
The second problem is that we eat tasty and none healthy food.
The third problem is that we do not know good recipes.

## Development

The launch point is a *Python* script `main.py`:

* It takes in a list of ingredients.
* It forecasts rating category of a potential dish with the ingredients.
* It finds all the nutrients in the ingredients as their daily values in `%`.
* It finds `3` the most similar recipes to the list of ingredients, their
  ratings, the URLs where a user can find the full details.

## Analytics

You need to prepare that is used above in a *Jupyter Notebook*s.

* Preprocessing:
  * Use dataset `food_recipes.csv` from *Epicurious* collected by *HugoDarwood*.
  * Filter the columns: you will predict the `rating`/`rating` category using
    the ingredients.

* Regression:
  * Calculate the *RMSE* metric score for a naive case that predicts the average
    `rating`.
  * Try different algorithms and their hyperparameters for `rating` prediction.
  * Choose the best model on *cross-validation* and find the *RMSE* metric score
    on the test data.
  * Try different ensembles and their hyperparameters.
  * Choose the best ensemble on *cross-validation* and find the *RMSE* metric
    score on the test data.

* Classification:
  * Calculate the *accuracy* metric score for a categorical naive case that
    predicts the most popular `rating` category.
  * Calculate the *accuracy* metric score for a class naive case that predicts
    the most popular `rating` class.
  * Try different algorithms and their hyperparameters for `rating`
    class/category prediction.
  * Choose the best model on *cross-validation* and find the metrics scores on
    the test data.
  * Try different ensembles and their hyperparameters.
  * Choose the best ensemble on *cross-validation* and find the metrics scores
    on the test data.

* Model selection:
  * Decide what is better: the regression model or the classification.
  * Save the best model.

* Nutritions:
  * Collect the nutrition information for the ingredients from your dataset into
    a *Pandas* dataframe.
    Use `https://fdc.nal.usda.gov/api-guide.html` *API*.
  * Transform the values into `%` of the daily nutritions norm.
  * Save the transformed *Pandas* dataframe.

* Recipes:
  * For each recipe from the dataset, collect the URL from `epicurious.com` with
    its details.
  * Save the new dataframe.

## Example

Your program should work as the example below:

```console
$ python main.py milk honey jam

I. THE FORECAST OF THE RECIPE RATING IS:
It is good idea to have a dish with that list of ingredients.

II. THE FACTS OF INGREDIENTS NUTRIENTS ARE:
Milk:
  * Protein - 6 % of daily value
  * Calcium - 12 % of daily value
  * Total Fat - 1 % of daily value
  * Total Carbohydrate - 1 % of daily value
...

III. TOP 3 SIMILAR RECIPES:
- Strawberry-Soy Milk Shake, rating: 3.0, URL:
https://www.epicurious.com/recipes/food/views/strawberry-soy-milk-
shake-239217
...
```

## Bonus functionality

The script perform a function: generate a menu for a day.
The menu should randomly give a list of the three recipes that cover the
nutritional needs without overtaking them and have the highest total rating.
You should offer recipes for: breakfast, lunch, dinner.

*Example*:

```console
IV. MENU FOR A DAY:

BREAKFAST
--------------------------------------------------------------------------------
Feta, Spinach, and Basil Omelette Muffins (rating: 4.375)
Ingredients:
- arugula
- egg
- feta
- muffin
- omelet
- spinach
- tomato
Nutrients:
- calories: 7.5 %
- protein: 16 %
- fat: 10 %
- sodium: 7 %
- ...
URL: https://www.epicurious.com/recipes/food/views/feta-spinach-and-basil-
omelette-muffins

LUNCH
--------------------------------------------------------------------------------
...
```
