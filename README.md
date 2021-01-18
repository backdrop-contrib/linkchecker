Link Checker
============

Installation:

1. Install linkchecker via Modules page.
2. Go to Modules and enable the "Link checker" module.
3. Go to Configuration -> Content authoring -> Link checker and enable the node types to scan.
4. Under "Link extraction" check all HTML tags that should be scanned.
5. Adjust the other settings if the defaults don't suit your needs.
6. Save configuration
7. Wait for cron to check all your links... this may take some time! :-)

If links are broken they appear under Reports -> Broken links.

If not, make sure cron is configured and running properly on your Backdrop
installation. The Link checker module also logs somewhat useful info about it's
activity under Reports -> Recent log messages.

Required:

1. For internal URL extraction you need to make sure that Cron always get called
   with your real public site URL (for e.g. https://example.com/cron.php). Make
   sure it's never executed with https://localhost/cron.php or any other
   hostnames or ports, not available from public. Otherwise all links may be
   reported as broken and cannot verified as they should be.

   To make sure it always works - it's required to configure the $base_url in
   the sites settings.php with your public sites URL. Better safe than sorry!

Known issues:

There are a lot of known issues in backdrop_http_request(). These have been solved
in HTTPRL. As a workaround it's recommended to use HTTPRL in linkchecker.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
<https://github.com/backdrop-contrib/linkchecker/issues>

Current Maintainers
-------------------

- Herb v/d Dool <https://github.com/herbdool>

Credits
-------

- Ported to Backdrop by Herb v/d Dool <https://github.com/herbdool>
- Originally developed for Drupal by joelstein <https://www.drupal.org/u/joelstein>.

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
