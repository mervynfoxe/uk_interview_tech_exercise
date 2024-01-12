<?php

/**
 * Implemements template_preprocess_views_view()
 */
function ukd8_preprocess_views_view(&$variables) {
    if (isset($variables['more'])) {
        $variables['more']['#options']['attributes']['class'][] = 'link--fancy';
    }
}

/**
 * Implemements template_form_views_exposed_form_alter()
 */
function ukd8_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  // Add view switcher for course list
  if (($form_id === 'views_exposed_form') && str_starts_with($form['#id'], 'views-exposed-form-courses-')) {
    $view_options = array(
      'list' => 'List',
      'card' => 'Grid'
    );
    $markup = '';

    // Generate list of possible views and their links
    foreach($view_options as $view => $label) {
      $query = \Drupal::request()->query->all();
      $route = 'view.courses.' . $view . '_page';
      // Build URL with current query strings
      $url = \Drupal\Core\Url::fromRoute($route);
      $url->setOptions(array('query' => $query));
      $markup .= '<li><a href="' . $url->toString() . '" class="' . ($route === \Drupal::routeMatch()->getRouteName() ? 'current' : '') . '">' . $label . '</a></li>';
    }

    $form['views_exposed_form'] = array('#markup' => '
      <div class="view-type-selector">
          <span class="label">View as:</span>
          <ul>' . $markup . '</ul>
      </div>
    ');
  }
}
